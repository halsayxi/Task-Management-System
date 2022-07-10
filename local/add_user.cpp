#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

extern string get_hash(string);

void add_user()
{
    string name;
    string pw, pw2, pw_in;
    
    //while循环用于密码输入不符合规范时
    while(1)
    {
        system("cls");

        cout<<"Please enter your user name:";
        cin>>name;
        cout<<"Please enter the new 6-digit password:";
        cin>>pw;
        cout<<"confirm your password:";
        cin>>pw2;

        if (pw == pw2 && pw.length() == 6) break;
        else cout<<"Wrong password. Failed to create a new account.\n";
        sleep(4);
    }

    pw_in = get_hash(pw);
    
    //新用户信息录入user文件
    ofstream out("users",ofstream::app);
    if (!out) {cerr<<"error! Unable to create the file."; return;}
    out<<name<<pw_in;
    out.close();

    //用于存放任务
    ofstream outfile(name); 
    if (!outfile) {cerr<<"error! Unable to create the file."; return;}
    outfile.close();

    cout<<"a new account created successfully!\n";
}