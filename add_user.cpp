#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

extern int debug;
extern string get_hash(string);
extern void DelLineData(string fileName);
void add_user()
{
    string name;
    string pw, pw2, pw_in;
    string fileData;

    
    //while循环用于密码输入不符合规范时
    while(1)
    {
        if (debug == 0) system("clear");
        else
        {
            cout << "\n========Adding user=========\n";
            sleep(2);
        }
        cout<<"\nPlease enter your user name(Space is forbidden):";
        if (debug == 0) cin>>name;
        else
        {
            ifstream testfile("testfile.txt");
            if (!testfile.is_open()) return;
            testfile >> name;
            testfile.close();
            DelLineData("testfile.txt");
            cout << name << "\n";
        }

        cout<<"\nPlease enter the new 6-digit password:";
        system("stty -echo");
        if (debug == 0) cin>>pw;
        else
        {
            ifstream testfile("testfile.txt");
            if (!testfile.is_open()) return;
            testfile >> pw;
            testfile.close();
            DelLineData("testfile.txt");
            cout << pw << "\n";
        }
        system("stty echo");
        cout<<endl;
        cout<<"\nConfirm your password:";
        system("stty -echo");
        if (debug == 0) cin>>pw2;
        else
        {
            ifstream testfile("testfile.txt");
            if (!testfile.is_open()) return;
            testfile >> pw2;
            testfile.close();
            DelLineData("testfile.txt");
            cout << pw2 << "\n";
        }
        system("stty echo");
        cout<<endl;

        //检查该账号是否已注册
        ifstream in("users");
        if (in)
        {
            while(getline(in,fileData))
            {
                if(!fileData.compare(name))
                {
                    cout<<"The user name is already used. Please choose another one.\n";
                    sleep(4);
                    return;
                }
            }
            in.close();
        }
        
        if (pw==pw2 && pw.length()==6) break;
        else cout<<"Wrong password. Failed to create a new account.\n";
        
        sleep(4);
    }
    
    pw_in = get_hash(pw);

    //新用户信息录入user文件
    ofstream out("users",ofstream::app);
    if (!out) {cerr<<"error! Unable to save the file.\n"; return;}
    out<<name<<endl;
    out<<pw_in<<endl;
    out.close();

    //用于存放任务
    ofstream outfile(name);
    if (!outfile) {cerr<<"error! Unable to create the file.\n"; return;}
    outfile.close();

    cout<<"A new account created successfully!\n";

    return;
}
