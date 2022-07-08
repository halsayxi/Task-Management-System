#include <add_user.h>

void add_user()
{
    string name;
    string pw, pw2, pw_in;
    
    while(1)
    {
        cout<<"请输入新用户名：";
        cin>>name;
        cout<<"请输入六位数新密码：";
        cin>>pw;
        cout<<"请确认新密码：";
        cin>>pw2;

        if (pw == pw2 && pw.length() == 6) 
        {
            cout<<"新账号创建成功！";
            break;
        }
        else cout<<"密码有误，新账号创建失败！";
    }
    
    pw_in = get_hash(pw);
    
    ofstream out("users",ofstream::app);
    if (!out) {cerr<<"error! Unable to create the file."; return;}
    out<<name<<pw_in;
    out.close();

    ofstream out(name);  //用于存放任务
    if (!out) {cerr<<"error! Unable to create the file."; return;}
    out.close();
}