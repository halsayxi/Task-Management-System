#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <login.h>
#include <add_user.h>
using namespace std;

int main()
{
    int choice;
    
    while(1)
    {
        cout<<"====欢迎使用日程管理系统===="<<endl;
        //sleep()
        cout<<"请选择您所需服务：\n1.注册新账号\n2.登录账号\n3.退出系统\n";
        cin>>choice;

        if (choice == 1) add_user();
        else if (choice == 2) login();
        else if (choice == 3) break;
        else cout<<"请输入1~3之间的整数!";
    }

    return 0;
}