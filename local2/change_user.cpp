#include <change_user.h>

void change_user(string Name, string Password)
{
    string name_new;
    string pw, pw_in, pw_new, pw_in_new;
    string fileData, taskData, userInfo, userInfo2;
    int location;

    cout<<"请输入密码";
    cin>>pw;

    if (pw != Password) {cout<<"密码错误！"; return;}

    pw_in = get_hash(pw);

    userInfo = Name + pw_in;

    cout<<"请输入新的用户名:";
    cin>>name_new;
    cout<<"请输入新的密码:";
    cin>>pw_new;

    pw_in_new = get_hash(pw_new);

    userInfo2 = name_new + pw_in_new;

    //删除user文件中原用户信息，加入新用户信息
    ifstream in("users");  
    if (!in) {cerr<<"error! Unable to open the file."; return;}
    in>>fileData;
    location = fileData.find(userInfo,0);
    fileData.erase(location, userInfo.length());
    fileData.insert(location, userInfo2);
    in.close();

    ofstream out("users");
    if (!out) {cerr<<"error! Unable to open the file."; return;}
    out<<fileData;
    out.close();

    //存放对应任务的文件改名
    ifstream in(Name);
    in>>taskData;
    in.close();

    ofstream out(name_new);
    out<<taskData;
    out.close();

    remove(reinterpret_cast<char*> (&Name));

    cout<<"账号修改成功！";
    //sleep();
    //system(clear);
}