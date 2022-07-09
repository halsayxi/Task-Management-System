#ifndef TASK
#define TASK
#include "user.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdio.h>
#include <queue>
#include <map>
#endif


void printMap(map<key,task>& m)
{
    for (map<key,task>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "name = " << it->second.name << "  start_time = " << it->second.start_time << endl;
    }
    cout << endl;
}

// accomplish the functions in class user

extern queue<string> cmdseq;
extern void input2cmdseq();
extern void clear_queue(queue<string>& q);


int task_process(user& usr, string cmd)
{
    if (cmd == "exit") exit(1);
    if (cmd == "showtask") usr.print_task(); // usr.print_task()
    if (cmd == "donetask") usr.done_task(); // usr.done_task()
    if (cmd == "deltask") usr.delete_task(); // usr.delete_task()
    if (cmd == "addtask") usr.insert_task(); // usr.insert_task()
    return 0;
}


string PRIO[4] = {"高", "中", "低"};
string CLAS[4] = {"学习", "娱乐", "生活"};
string DONE[3] ={"已完成", "未完成"};


//文件读取
class FileError: public exception
{
    private:
    string error_msg;
    public:
    FileError(string msg):error_msg(msg){};
    virtual const char * what() const noexcept override
    {return error_msg.c_str();}
};

void ReadFile(const string& filename)//目前没有用上 但是后续可以将assert改成try&throw
{
    fstream in;
    in.open(filename,fstream::in);
    
    if(in.fail())
    {
        string error = "读取文件失败。";
        throw FileError(error);
    }
}


string cmdseq_to_file_time()
{
    string input_str=cmdseq.front();//获取输入时间 格式为dd/mm[/yyyy]_[hh][:mm], [日期/月份/年份_小时:分钟:00]
    cmdseq.pop();
    string ans="2022-00-00 08:00:00";
    bool is_time=false;
    string::size_type pos;

    pos=input_str.find("_");
    if (pos==input_str.npos)//没有输入hhmm
    {
        is_time = false;
    }
    else
    {
        is_time = true;
    }

    string ddmmyyyy = "", hhmm = "";
    if (is_time)
    {
        ddmmyyyy=input_str.substr(0,pos);
        hhmm=input_str.substr(pos+1);
    }
    else
    {
        ddmmyyyy = input_str;
    }

    //cout << input_str << endl;
    //cout << ddmmyyyy << endl;
    //cout << hhmm << endl;


    ans[8] = ddmmyyyy[0];
    ans[9] = ddmmyyyy[1];

    ans[5] = ddmmyyyy[3];
    ans[6] = ddmmyyyy[4];


    if (ddmmyyyy.length()>5)
    {
        ans[0] = ddmmyyyy[6];
        ans[1] = ddmmyyyy[7];
        ans[2] = ddmmyyyy[8];
        ans[3] = ddmmyyyy[9];
    }

    if (is_time)
    {
        ans[11] = hhmm[0];
        ans[12] = hhmm[1];
        if (hhmm.length() > 3)
        {
            ans[14] = hhmm[3];
            ans[15] = hhmm[4];
        }
    }
    return ans;
}

void user::insert_task()//任务录入
{
    ofstream outfile;
    outfile.open(_id,ofstream::app);
    if(outfile.fail())
    {
        cerr<<"错误：打开文件失败。"<<endl;
        assert(0);
    }
    /*
        文件已打开，开始执行任务录入，需要录入以下属性
        int task_id;//唯一的index
        string name;//任务名称
        int type;//任务类型 缺省值为生活
        int priority;//任务优先级 缺省值为低
        string remind_time;//提醒时间
        string start_time;//启动时间
        bool flag;//是否已完成 完成为true
        bool remind_flag;//是否已提醒 已提醒为true//不存入文件
    */
    task tmp_task;
    key tmp_key;

    tmp_task.task_id=count;
    count=count+1;

    
    if(cmdseq.size()!=0) clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("请输入任务名称\n > ");
        input2cmdseq();
    }
    tmp_task.name=cmdseq.front();
    tmp_key.name=cmdseq.front();
    cmdseq.pop();
    
    clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("请输入任务类型\n您可以输入学习||娱乐||生活\n若输入为空或者输入其他内容，默认任务类型为生活\n > ");
        input2cmdseq();
    }
    if((cmdseq.front()=="学习") || (cmdseq.front()=="Study"))
        tmp_task.type=0;
    else if((cmdseq.front()=="娱乐") || (cmdseq.front()=="Entertainment"))
        tmp_task.type=1;
    else
        tmp_task.type=2;
    cmdseq.pop();
         
    if(cmdseq.size()==0)
    {
        printf("请输入任务优先级\n您可以输入高||中||低\n若输入为空或者输入其他内容，默认任务优先级为低\n > ");
        input2cmdseq();
    }
    if((cmdseq.front()=="高")||(cmdseq.front()=="High"))
        tmp_task.priority=0;
    else if((cmdseq.front()=="中")||(cmdseq.front()=="Medium"))
        tmp_task.priority=1;
    else
        tmp_task.priority=2;
    cmdseq.pop();
        
    if(cmdseq.size()==0)
    {
        printf("请输入任务提醒时间\n格式为dd/mm[/yyyy]_[hh][:mm], [日期(必需)/月份(必需)/年份_小时:分钟]\n示例：01/01/2021_12:30 或者 01/01 或者 01/01/2021\n > ");
        input2cmdseq();
    }
    tmp_task.remind_time=cmdseq_to_file_time();

    if(cmdseq.size()==0)
    {
        printf("请输入任务启动时间\n格式为dd/mm[/yyyy]_[hh][:mm], [日期(必需)/月份(必需)/年份_小时:分钟]\n示例：01/01/2021_12:30 或者 01/01 或者 01/01/2021\n > ");
        input2cmdseq();
    }
    tmp_task.start_time=cmdseq_to_file_time();
    tmp_key.start_time=tmp_task.start_time;
    
    tmp_task.flag=false;
    tmp_task.remind_flag=false;
    
    //将tmp_task添加到mytask队尾
    mytask.insert(make_pair(tmp_key,tmp_task));
    //printMap(mytask);
    
    //将任务tmp_task写入文件
    outfile<<tmp_task.name<<endl;
    outfile<<tmp_task.start_time<<endl;//把任务名称和任务启动时间放在前两行，方便后续比较
    outfile<<tmp_task.task_id<<endl;
    outfile<<tmp_task.type<<endl;
    outfile<<tmp_task.priority<<endl;
    outfile<<tmp_task.remind_time<<endl;
    if(tmp_task.flag==false)
        outfile<<"未完成"<<endl;
    else outfile<<"已完成"<<endl;
    outfile.close();
    printf("录入任务成功！\n");
}

void user::delete_task()//任务删除
{
    fstream in;
    in.open(_id, ios::in);//原文件
    fstream out;
    out.open("tmp", ios::out);//中间文件
    if(in.fail())
    {
        cerr<<"错误：打开文件失败。"<<endl;
        assert(0);
    }
    
    //根据任务名称+开始时间具有唯一性，确定要删除的任务
    string _name,_time,estr;
    if(cmdseq.size()!=0)
    clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("请输入需要删除的任务名称\n > ");
        input2cmdseq();
    }
    _name=cmdseq.front();
    cmdseq.pop();
    if(cmdseq.size()==0)
    {
        printf("请输入需要删除的任务启动时间\n格式为dd/mm[/yyyy]_[hh][:mm], [日期(必需)/月份(必需)/年份_小时:分钟]\n示例：01/01/2021_12:30 或者 01/01 或者 01/01/2021\n > ");
        input2cmdseq();
    }
    _time=cmdseq_to_file_time();

    //在任务map中删除该任务
    key key1;
    key1.name=_name;
    key1.start_time=_time;
    mytask.erase(key1);
    
    //在文件中删除该任务
    while(getline(in,estr))//得到原文件中一行的内容
    {
        if (!estr.compare(_name))//比较原文件每一行的内容和要删除的是否一致，一致就跳过
        {
            getline(in,estr);
            if(!estr.compare(_time))
            {
                getline(in,estr);getline(in,estr);getline(in,estr);getline(in,estr);getline(in,estr);
                continue;
            }
            else
            {
                out<<_name<<"\n";
            }
        }
        out<<estr<<"\n";//不一致的内容写到中间文件中，注意换行
    }
    in.close();//关闭流
    out.close();
    fstream outfile(_id, ios::out);
    fstream infile("tmp", ios::in);
    while(getline(infile, estr)) //将中间文件的内容写到原文件（覆盖）
    {
        outfile<<estr<<"\n";
    }
    const char* path = "tmp";
    remove(path);//删除tmp.txt
    outfile.close();//关闭流
    infile.close();
    printf("删除任务成功！\n");
}

void user::done_task()//任务完成
{
    fstream in(_id, ios::in);//原文件
    fstream out("tmp", ios::out);//中间文件
    if(in.fail())
    {
        cerr<<"错误：打开文件失败。"<<endl;
        assert(0);
    }
    
    //根据任务名称+开始时间具有唯一性，确定完成的任务
    string _name,_time,estr;
    if(cmdseq.size()!=0)
    clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("请输入已完成任务的名称\n > ");
        input2cmdseq();
    }
    _name=cmdseq.front();
    cmdseq.pop();
    if(cmdseq.size()==0)
    {
        printf("请输入已完成任务的启动时间\n格式为dd/mm[/yyyy]_[hh][:mm], [日期(必需)/月份(必需)/年份_小时:分钟]\n示例：01/01/2021_12:30 或者 01/01 或者 01/01/2021\n > ");
        input2cmdseq();
    }
    _time=cmdseq_to_file_time();
    
    //在任务map中标记该任务已完成
    key key1;
    key1.name=_name;
    key1.start_time=_time;
    mytask[key1].flag=true;
    
    //在文件中标记该任务已完成
    while(getline(in,estr))//得到原文件中一行的内容
    {
        if (!estr.compare(_name))//比较原文件每一行的内容和要删除的是否一致，一致就跳过
        {
            out<<estr<<"\n";
            getline(in,estr);
            if(!estr.compare(_time))
            {
                out<<estr<<"\n";
                getline(in,estr);out<<estr<<"\n";
                getline(in,estr);out<<estr<<"\n";
                getline(in,estr);out<<estr<<"\n";
                getline(in,estr);out<<estr<<"\n";
                out<<"已完成"<<"\n";
                getline(in,estr);
                continue;
            }
        }
        out<<estr<<"\n";//不一致的内容写到中间文件中，注意换行
    }
    in.close();//关闭流
    out.close();
    fstream outfile(_id, ios::out);
    fstream infile("tmp", ios::in);
    while(getline(infile, estr)) //将中间文件的内容写到原文件（覆盖）
    {
        outfile<<estr<<"\n";
    }
    const char* path = "tmp";
    remove(path);//删除tmp.txt
    outfile.close();//关闭流
    infile.close();
    printf("已标记完成改任务！\n");
}

void user::print_task()//任务显示 根据启动时间
{
    if(user::mytask.size()==0)
    {
        printf("没有任何计划事项捏。\n");
        return;
    }
    task tmp_task;

    
    printf("|%-22s|%-10s|%-11s|%-9s|%-26s|%-26s|%-10s|\n", "任务名称", "任务ID", "优先级", "分类", "启动时间",  "提醒时间","完成状况");
    // id done name time prio class alarm
    printf("|----------------|-------|-------|-------|---------------------|--------------------|-------|\n");
    
    for(auto &t : user::mytask)
    {
        tmp_task=t.second;
        //printf("|%-22s|%d|%-10s|%-10s|%-20s|%-20s|",tmp_task.name.c_str(),tmp_task.task_id,PRIO[tmp_task.priority].c_str(),CLAS[tmp_task.type].c_str(),tmp_task.start_time.c_str(),tmp_task.remind_time.c_str();
        //cout<<tmp_task.start_time<<endl;
        //cout<<tmp_task.remind_time<<endl;
        printf("|%-16s|",tmp_task.name.c_str());
        string str=to_string(tmp_task.task_id);
        printf("%-7s|",str.c_str());
        printf("%-9s|",PRIO[tmp_task.priority].c_str());
        printf("%-9s|",CLAS[tmp_task.type].c_str());
        cout<<" "<<tmp_task.start_time<<" |";
        cout<<" "<<tmp_task.remind_time<<" |";
        
        if(tmp_task.flag==true)
            printf("%-10s|\n",DONE[0].c_str());
        else
            printf("%-10s|\n",DONE[1].c_str());
    }
    printf("任务显示完毕！\n");
    
    /*
    fstream in;
    in.open(_id, ios::in);
    if(in.fail())
    {
        cerr<<"错误：打开文件失败。"<<endl;
        assert(0);
    }
    string name_;
    string id_;
    string prio_;
    string type_;
    string starttime1;string starttime2;
    string remindtime1;string remindtime2;
    string flag_;
    int prio;int type;
        
    while (1)
    {
        in>>name_;
        
        if(in.eof())
        {
            printf("任务显示完毕！\n");
            break;
        }
        
        in>>starttime1;in>>starttime2;
        in>>id_;
        
        in>>type_;
        if(type_=="0") type=0;
        else if(type_=="1") type=1;
        else type=2;
        
        in>>prio_;
        if(prio_=="0") prio=0;
        else if(prio_=="1") prio=1;
        else prio=2;
        
        in>>remindtime1;in>>remindtime2;
        in>>flag_;
        
        cout<<name_<<' '<<id_<<' '<<PRIO[prio]<<' '<<CLAS[type]<<' '<<starttime1<<' '<<starttime2<<' '<<remindtime1<<' '<<remindtime2<<' '<<flag_<<endl;
    }
    */
}

int string2int(string str)
{
    stringstream stream;  //声明一个之后所需的流对象
    int n;
    stream<<str;
    stream>>n;
    stream.clear();//同一个流对象两次使用时应该用clear函数清除流标志，否则下一块就不起作用
    return n;
}

bool isFileExists_ifstream(string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

void user::load_task()//任务加载
{
    if(!isFileExists_ifstream(_id)) return;
    fstream in;
    in.open("whx", ios::in);
    if(in.fail())
    {
        cerr<<"错误：打开文件失败。"<<endl;
        assert(0);
    }
    
    string name_;
    string id_;
    string prio_;
    string type_;
    string starttime1;string starttime2;
    string remindtime1;string remindtime2;
    string flag_;
    int prio;int type;
    
    key tmp_key;
    task tmp_task;
        
    while (1)
    {
        in>>name_;
        
        if(in.eof())
        {
            printf("任务加载完毕！\n");
            break;
        }
        
        in>>starttime1;in>>starttime2;
        
        in>>id_;
        
        in>>type_;
        if(type_=="0") type=0;
        else if(type_=="1") type=1;
        else type=2;
        
        in>>prio_;
        if(prio_=="0") prio=0;
        else if(prio_=="1") prio=1;
        else prio=2;
        
        in>>remindtime1;in>>remindtime2;
        
        in>>flag_;
        
        tmp_key.name=name_;
        tmp_task.name=name_;
        
        //cout<<starttime1<<endl;
        //cout<<starttime2<<endl;
        tmp_key.start_time=starttime1.append(" ").append(starttime2);
        //cout<<tmp_key.start_time<<endl;
        //cout<<"完毕！"<<endl;
        tmp_task.start_time=tmp_key.start_time;
        
        tmp_task.task_id=string2int(id_);
        tmp_task.type=string2int(type_);
        tmp_task.priority=string2int(prio_);
        
        
        //cout<<remindtime1<<endl;
        //cout<<remindtime2<<endl;
        tmp_task.remind_time=remindtime1.append(" ").append(remindtime2);
        //cout<<tmp_task.remind_time<<endl;
        //cout<<"完毕！"<<endl;
        
        if(flag_=="未完成")
            tmp_task.flag=false;
        else tmp_task.flag=true;
        tmp_task.remind_flag=false;//任务加载时默认该任务没有被提醒过 需要被重新提醒
        
        mytask.insert(make_pair(tmp_key,tmp_task));
        
    }
}


