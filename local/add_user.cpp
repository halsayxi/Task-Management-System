#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <string>

using namespace std;

extern string get_hash(string);

void add_user()
{
    string name;
    string pw, pw2, pw_in;
    string fileData;
    bool flag = false; 
    char ch;  //用来获取键盘输入
    
    //while循环用于密码输入不符合规范时
    while(1)
    {
        system("cls");
        cout<<"Please enter your user name(Space is forbidden):";
        cin>>name;
        cout<<"Please enter the new 6-digit password:";
        while ((ch=_getch())!=13)  //回车键ASCII码是13
        {
            pw+=ch;//string对象重载了+=
            cout<<"*";
        }
        cout<<endl;
        cout<<"confirm your password:";
        while ((ch=_getch())!=13)
        {
            pw2+=ch;//string对象重载了+=
            cout<<"*";
        }

        //检查该账号是否已注册
        ifstream in("users");  
        if (in) 
        {
            while(getline(in,fileData))
            {
                if(!fileData.compare(name)) 
                {
                    cout<<"The user name is already used. Please choose another one.\n";
                    flag = true; 
                    break;
                }
            }
            in.close();
        }
        if (!flag)
        {
            if (pw == pw2 && pw.length() == 6) break;
            else cout<<"Wrong password. Failed to create a new account.\n";
        }
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

    cout<<"a new account created successfully!\n";
}