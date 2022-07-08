#include<login.h>
#include <print_user.h>
#include <change_user.h>
#include <delete_user.h>
#include <task_management.h>

void login()
{
    string name;
    string pw, pw_in;
    string userInfo;
    string fileData;
    int location;
    int choice2;

    while(1)
    {
        cout<<"请输入用户名";
        cin>>name;
        cout<<"请输入密码";
        cin>>pw;

        pw_in = get_hash(pw);
        
        userInfo = name + pw_in;

        ifstream in("users");  //从user文件中查找用户信息
        if (!in) {cerr<<"error! Unable to open the file."; return 1;}
        in>>fileData;
        location = fileData.find(userInfo,0);
        if (location != -1) break;
        else cout<<"用户名或密码错误！请重新输入！";
        in.close();
    }
    
    cout<<"欢迎您！用户"<<name<<endl;
    
    while(1)
    {
        cout<<"请选择您所需服务：\n1.显示账号信息\n2.修改账号信息\n3.注销账号\n4.日程任务管理\n5.退出账号\n";
        cin>>choice2;

        switch(choice2)
        {
            case 1: print_user(name, pw); break;
            case 2: change_user(name, pw);break;
            case 3: delete_user(name, pw_in);break;
            case 4: task_management();break;
            case 5: return;
            default: cout<<"请输入1~5之间的整数!";
        }
    }
}
    