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
#include <stdlib.h>
#include <queue>
#include <map>
#include <ctime>
#endif


void printMap(map<key,task>& m)
{
    for (map<key,task>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "name = " << it->second.name << "  start_time = " << it->second.start_time << endl;
        cout << "id = " << it->second.task_id << endl;
    }
    cout << endl;
}

// accomplish the functions in class user
extern mutex m; // for multithread use -- lock
extern queue<string> cmdseq;
extern void input2cmdseq();
extern void clear_queue(queue<string>& q);

void process_all(user& usr)
{
    string cmd;
    while(1)
    {
        if(cmdseq.size()==0)
        {
            printf("请输入\nshowtask || donetask || deltask || addtask || exit\n > ");
            input2cmdseq();
        }
        cmd=cmdseq.front();
        cmdseq.pop();
        task_process(usr,cmd);
    }
}

int task_process(user& usr, string cmd)
{
    if (cmd == "exit") usr.exit_task();
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

    
    if(cmdseq.size()!=0) clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("请输入任务名称\n > ");
        input2cmdseq();
    }
    tmp_task.name=cmdseq.front();
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
    string tmp=tmp_task.start_time;
    
    string::size_type pos;
    string yyyy = "", mm = "", dd = "", hh = "", ff = "", ss = "00", other1 = "", other2 = "";
    
    pos=tmp.find("-");
    yyyy=tmp.substr(0,pos);
    other1=tmp.substr(pos+1);
    
    pos=other1.find("-");
    mm=other1.substr(0,pos);
    other2=other1.substr(pos+1);
    
    pos=other2.find(" ");
    dd=other2.substr(0,pos);
    other1=other2.substr(pos+1);
    
    pos=other1.find(":");
    hh=other1.substr(0,pos);
    other2=other1.substr(pos+1);
    
    pos=other2.find(":");
    ff=other2.substr(0,pos);
    other1=other2.substr(pos+1);

    count=count+1;
    std::string tmp_count = std::to_string(count);
    tmp_task.task_id=yyyy.append(mm).append(dd).append(hh).append(ff).append(ss).append(tmp_count);
    tmp_key.task_id=tmp_task.task_id;
    
    
    tmp_task.flag=false;
    tmp_task.remind_flag=false;
    
    //将tmp_task添加到mytask队尾
    unique_lock<mutex> g1(m, try_to_lock);
    if (g1.owns_lock())
    {
        mytask.insert(make_pair(tmp_key,tmp_task));
    }
    else
    {
        cout << "\nLock Error when add task!\n";
    }
    g1.unlock();
    //printMap(mytask);
    
    //将任务tmp_task写入文件
    outfile<<tmp_task.task_id<<endl;//把任务id放在最前面，方便后续比较
    outfile<<tmp_task.name<<endl;
    outfile<<tmp_task.start_time<<endl;
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
    
    bool del_flag=false;
    //根据任务id具有唯一性，确定要删除的任务
    string id,estr;
    if(cmdseq.size()!=0)
    clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("请输入需要删除的任务id\n > ");
        input2cmdseq();
    }
    id=cmdseq.front();
    cmdseq.pop();


    //在文件中删除该任务
    while(getline(in,estr))//得到原文件中一行的内容
    {
        if (!estr.compare(id))//比较原文件每一行的内容和要删除的是否一致，一致就跳过
        {
            getline(in,estr);
            getline(in,estr);
            getline(in,estr);
            getline(in,estr);
            getline(in,estr);
            getline(in,estr);
            del_flag=true;
            continue;
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
    if(del_flag)
    {
        //在任务map中删除该任务
        unique_lock<mutex> g1(m, try_to_lock);
        if (g1.owns_lock())
        {
            key key1;
            key1.task_id=id;
            mytask.erase(key1);
        }
        else
        {
            cout << "\nLock Error when delete task!\n";
        }
        g1.unlock();
        
        printf("删除任务成功！\n");
    }
        
    else
        printf("未找到该任务！\n");
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
    
    bool done_flag=false;
    //根据任务id具有唯一性，确定完成的任务
    string id,estr;
    if(cmdseq.size()!=0)
    clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("请输入已完成的任务id\n > ");
        input2cmdseq();
    }
    id=cmdseq.front();
    cmdseq.pop();
    
    //在文件中标记该任务已完成
    while(getline(in,estr))//得到原文件中一行的内容
    {
        if (!estr.compare(id))//比较原文件每一行的内容和要删除的是否一致，一致就跳过
        {
            out<<estr<<"\n";
            getline(in,estr);out<<estr<<"\n";
            getline(in,estr);out<<estr<<"\n";
            getline(in,estr);out<<estr<<"\n";
            getline(in,estr);out<<estr<<"\n";
            getline(in,estr);out<<estr<<"\n";
            out<<"已完成"<<"\n";
            getline(in,estr);
            done_flag=true;
            //cout<<"找到并修改！"<<endl;
            continue;
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
    if(done_flag)
    {
        //在任务map中标记该任务已完成
        unique_lock<mutex> g1(m, try_to_lock);
        if (g1.owns_lock())
        {
            key key1;
            key1.task_id=id;
            mytask[key1].flag=true;
        }
        else
        {
            cout << "\nLock Error when done task!\n";
        }
        g1.unlock();
        
        printf("已标记完成该任务！\n");
    }
        
    else
        printf("未找到该任务！\n");
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

bool compare_mon(task tmp_task)
{
    bool flag=true;
    time_t nowtime;
    struct tm* p;
    time(&nowtime);
    p=localtime(&nowtime);

    string yyyy=std::to_string(p->tm_year+1900);
    string mm=std::to_string(p->tm_mon+1);
    string zero="0";
    if(mm.length()==1)
    {
        string new_mm;
        new_mm=zero.append(mm);
        mm=new_mm;
    }
    string task_time=tmp_task.start_time;
    if(task_time[0]!=yyyy[0] || task_time[1]!=yyyy[1] || task_time[2]!=yyyy[2] || task_time[3]!=yyyy[3])//比较年份
        flag=false;
    if(task_time[5]!=mm[0] || task_time[6]!=mm[1])//比较月份
        flag=false;
    return flag;
}

bool compare_day(task tmp_task)
{
    bool flag=true;
    time_t nowtime;
    struct tm* p;
    time(&nowtime);
    p=localtime(&nowtime);

    string yyyy=std::to_string(p->tm_year+1900);
    string mm=std::to_string(p->tm_mon+1);
    string dd=std::to_string(p->tm_mday);
    string zero="0";
    if(mm.length()==1)
    {
        string new_mm;
        new_mm=zero.append(mm);
        mm=new_mm;
    }
    zero="0";
    if(dd.length()==1)
    {
        string new_dd;
        new_dd=zero.append(dd);
        dd=new_dd;
    }
    string task_time=tmp_task.start_time;
    if(task_time[0]!=yyyy[0] || task_time[1]!=yyyy[1] || task_time[2]!=yyyy[2] || task_time[3]!=yyyy[3])//比较年份
        flag=false;
    if(task_time[5]!=mm[0] || task_time[6]!=mm[1])//比较月份
        flag=false;
    if(task_time[8]!=dd[0] || task_time[9]!=dd[1])//比较日期
        flag=false;
    return flag;
}

void user::print_task()//任务显示 根据启动时间
{
    string option;
    if(cmdseq.size()!=0)
    clear_queue(cmdseq);
    if(cmdseq.size()==0)
    {
        printf("查看所有任务请输入0 查看本月任务请输入1 查看本日任务请输入2\n > ");
        input2cmdseq();
    }
    option=cmdseq.front();
    cmdseq.pop();
    
    if(option=="0")
    {
        if(user::mytask.size()==0)
        {
            printf("没有任何计划事项捏。\n");
            return;
        }
        task tmp_task;

        
        printf("|%-22s|%-20s|%-12s|%-9s|%-26s|%-26s|%-10s|\n", "任务名称", "任务ID", "优先级", "分类", "启动时间",  "提醒时间","完成状况");
        // id done name time prio class alarm
        printf("|----------------|-----------------|-------|-------|---------------------|--------------------|-------|\n");
        
        for(auto &t : user::mytask)
        {
            tmp_task=t.second;
            printf("|%-16s|",tmp_task.name.c_str());
            cout<<" "<<tmp_task.task_id<<" |";
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
    }
    else if(option=="1")
    {

        bool have_task=false;
        task tmp_task;

        
        printf("|%-22s|%-20s|%-11s|%-9s|%-26s|%-26s|%-10s|\n", "任务名称", "任务ID", "优先级", "分类", "启动时间",  "提醒时间","完成状况");
        // id done name time prio class alarm
        printf("|----------------|-----------------|-------|-------|---------------------|--------------------|-------|\n");
        
        for(auto &t : user::mytask)
        {
            tmp_task=t.second;
            if(!compare_mon(tmp_task)) continue;
            else
            {
                printf("|%-16s|",tmp_task.name.c_str());
                cout<<" "<<tmp_task.task_id<<" |";
                printf("%-9s|",PRIO[tmp_task.priority].c_str());
                printf("%-9s|",CLAS[tmp_task.type].c_str());
                cout<<" "<<tmp_task.start_time<<" |";
                cout<<" "<<tmp_task.remind_time<<" |";
                
                if(tmp_task.flag==true)
                    printf("%-10s|\n",DONE[0].c_str());
                else
                    printf("%-10s|\n",DONE[1].c_str());
                have_task=true;
            }
        }
        if(have_task==false)
            printf("没有任何计划事项捏。\n");
        else
            printf("任务显示完毕！\n");
    }
    else
    {
        bool have_task=false;
        task tmp_task;

        
        printf("|%-22s|%-20s|%-11s|%-9s|%-26s|%-26s|%-10s|\n", "任务名称", "任务ID", "优先级", "分类", "启动时间",  "提醒时间","完成状况");
        // id done name time prio class alarm
        printf("|----------------|-----------------|-------|-------|---------------------|--------------------|-------|\n");
        
        for(auto &t : user::mytask)
        {
            tmp_task=t.second;
            if(!compare_day(tmp_task)) continue;
            else
            {
                printf("|%-16s|",tmp_task.name.c_str());
                cout<<" "<<tmp_task.task_id<<" |";
                printf("%-9s|",PRIO[tmp_task.priority].c_str());
                printf("%-9s|",CLAS[tmp_task.type].c_str());
                cout<<" "<<tmp_task.start_time<<" |";
                cout<<" "<<tmp_task.remind_time<<" |";
                
                if(tmp_task.flag==true)
                    printf("%-10s|\n",DONE[0].c_str());
                else
                    printf("%-10s|\n",DONE[1].c_str());
                have_task=true;
            }
        }
        if(have_task==false)
            printf("没有任何计划事项捏。\n");
        else
            printf("任务显示完毕！\n");
    }

}



bool isFileExists_ifstream(string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

void user::load_task()//任务加载
{
    if(!isFileExists_ifstream(_id))
    {
        printf("任务加载完毕！\n");
        return;
    }
    fstream in;
    in.open(_id, ios::in);
    if(in.fail())
    {
        cerr<<"错误：打开任务文件失败。"<<endl;
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
        in>>id_;
    
        if(in.eof())
        {
            break;
        }
        
        in>>name_;
        
        in>>starttime1;in>>starttime2;
        
    
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
        
        //cout<<id1<<endl;
        //cout<<id2<<endl;
        tmp_key.task_id=id_;
        tmp_task.task_id=tmp_key.task_id;
        //cout<<tmp_key.task_id<<endl;
        
        tmp_task.name=name_;
        tmp_task.start_time=starttime1.append(" ").append(starttime2);
        
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
    in.close();
    
    string tmp_id=_id;
    string file_count=tmp_id.append("count");
    if(!isFileExists_ifstream(file_count))
    {
        printf("任务加载完毕！\n");
        return;
    }
    in.open(file_count, ios::in);
    if(in.fail())
    {
        cerr<<"错误：打开计数文件失败。"<<endl;
        assert(0);
    }
    in>>count;
    //cout<<count<<endl;
    in.close();
    in.open(file_count, ios::trunc);
    in.close();
    
    printf("任务加载完毕！\n");
}



void user::exit_task()//退出
{
    fstream out;
    string tmp_id=_id;
    string file_count=tmp_id.append("count");
    out.open(file_count, ios::out);
    if(out.fail())
    {
        cerr<<"错误：打开文件失败。"<<endl;
        assert(0);
    }
    out<<count<<endl;
    out.close();
    exit(1);
}
