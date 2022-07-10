#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

extern string get_hash(string);
extern void print_user(string, string);
extern void change_user(string, string);
extern void delete_user(string, string);
extern void task_management(void);


int login()
{
    string name;
    string pw, pw_in;
    string userInfo;
    string fileData;
    int location;
    int choice2;
    
    //while循环用于找不到用户信息时
    while(1)
    {
        system("cls");
        cout<<"Please enter your user name:";
        cin>>name;
        cout<<"Please enter the password:";
        cin>>pw;

        pw_in = get_hash(pw);
        
        userInfo = name + pw_in;

        ifstream in("users");  //从user文件中查找用户信息
        if (!in) {cerr<<"error! Unable to open the file."; return -1;}
        in>>fileData;
        location = fileData.find(userInfo,0);
        if (location != -1) break;
        else cout<<"The user name or password is wrong! Please enter them again.";
        in.close();
        sleep(4);
    }
    
    cout<<"welcome! User "<<name<<endl;
    
    //while循环用于回到原界面
    while(1)
    {
        system("cls");
        cout<<"Please choose the sevice you need:\n1.print account information\n2.change account information\n3.delete this account\n4.task management\n5.quit\n";
        cin>>choice2;

        switch(choice2)
        {
            case 1: print_user(name, pw); break;
            case 2: change_user(name, pw); return 0;
            case 3: delete_user(name, pw_in); return 0;
            case 4: task_management(); break;
            case 5: return 1;          //返回1，跳回原函数后不挂起
            default: cout<<"Please input an integer between 1 and 5!\n";
        }
        sleep(4);
    }
}
    