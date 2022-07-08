#include <print_user.h>

void print_user(string Name, string Password)
{
    string pw, pw_in;   
    string userInfo, fileData;
    
    cout<<"请输入密码";
    cin>>pw;

    if (pw != Password) {cout<<"密码错误！"; return;}

    cout<<"用户名："<<Name<<endl;
    cout<<"密码："<<Password<<endl;
    //sleep();
}