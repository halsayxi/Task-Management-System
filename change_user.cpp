#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

extern string get_hash(string);

extern bool isFileExists_ifstream(string& name);

void change_user(string Name, string Password)
{
    string name_new;
    string pw, pw_new, pw_in_new;
    string fileData, taskData;
    bool flag = false;
    int flag_2;
    
    system("clear");
    
    cout<<"Please enter current password:";
    system("stty -echo");
    cin>>pw;
    system("stty echo");
    cout<<endl;

    if (pw != Password)
    {
        cout<<"Wrong password!";
        sleep(4);
        return;
    }

    //while循环用于输入不符合规范时
    while(1)
    {
        system("clear");
        cout<<"Please enter new user name:";
        cin>>name_new;
        cout<<"Please enter new password:";
        system("stty -echo");
        cin>>pw_new;
        system("stty echo");
        cout<<endl;

        //检查该账号是否已注册
        ifstream in("users.data");  
        if(in) 
        {
            while(getline(in,fileData))
            {
                if(!fileData.compare(name_new)) 
                {
                    if (fileData != Name)
                    {
                        cout<<"The user name is already used. Please choose another one.\n";
                        flag = true; 
                        break;
                    }
                }
            }
            in.close();
        }
        else
        {
            cerr<<"No account existed! Please register an account first.\n";
            sleep(4);
            return;
        }

        //账户未注册，可修改
        if(!flag)  
        {
            if(pw_new.length() != 6) cout<<"The password must be 6-digited!\n";
            else
            {
                pw_in_new = get_hash(pw_new);

                if(Name!=name_new)
                {
                    //删除user文件中原用户信息，加入新用户信息
                    ifstream in("users.data");
                    if (!in)
                    {
                        cerr<<"No account existed! Please register an account first.\n";
                        sleep(4);
                        return;
                    }
                    ofstream out("tmp.data");

                    while(getline(in,fileData))//得到原文件中一行的内容
                    {
                        if (!fileData.compare(Name))//比较原文件每一行的内容和要删除的是否一致，一致就跳过
                        {
                          getline(in,fileData);
                          out<<name_new<<endl;
                          out<<pw_in_new<<endl;     //加入新用户信息
                          continue;
                        }
                        out<<fileData<<"\n";//不一致的内容写到中间文件中，注意换行
                    }
     
                    in.close();//关闭流
                    out.close();
                    fstream outfile("users.data", ios::out);
                    fstream infile("tmp.data", ios::in);
                    while(getline(infile, fileData)) //将中间文件的内容写到原文件（覆盖）
                    {
                        outfile<<fileData<<"\n";
                    }
                    outfile.close();//关闭流
                    infile.close();
                  
                    const char* path = "tmp.data";
                    remove(path);//删除tmp
     
                    //存放对应任务的文件改名
                    string data_name = Name + ".data";
                    string data_name_new = name_new + ".data";
                    ifstream in2(data_name);
                    ofstream out2(data_name_new);

                    while(getline(in2,taskData))//得到原文件中一行的内容
                    {
                        out2<<taskData<<"\n";
                    }

                    in2.close();//关闭流
                    out2.close();
                
                    const char* filePath_3 = (Name + ".data").data();
                    flag_2 = remove(filePath_3);

                    if (flag_2 != 0)
                    {
                        cout<<"Fail to change the file!\n";
                        sleep(4);
                        return;
                    }

                    //“用户名+count”文件改名
                    string filename = Name + "count" + ".data";
                    if(isFileExists_ifstream(filename))
                    {
                        string filename_new = name_new + "count" + ".data";
                        ifstream in3(filename);
                        ofstream out3(filename_new);
                        in3>>taskData;
                        out3<<taskData;

                        in3.close();//关闭流
                        out3.close();
                        const char* filePath = filename.data();
                        flag_2 = remove(filePath);
                        if (flag_2 != 0)
                        {
                            cout<<"Fail to change the file!\n";
                            sleep(4);
                            return;
                        }
                    }
                }

                cout<<"Account information changed successfully!\n";
                break;
            }
        }
        sleep(4);
    }
}
