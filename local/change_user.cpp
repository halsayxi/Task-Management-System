#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;

extern string get_hash(string);

void change_user(string Name, string Password)
{
    string name_new;
    string pw, pw_in, pw_new, pw_in_new;
    string fileData, taskData, userInfo, userInfo2;
    int location, flag;
    string filePath = "C:\\Users\\86177\\Desktop\\code\\user";
    filePath = filePath + Name;
    //strcat(savePath, reinterpret_cast<char*>(&Name));

    cout<<"Please enter the password:";
    cin>>pw;

    if (pw != Password) {cout<<"Wrong password!"; return;}

    pw_in = get_hash(pw);

    userInfo = Name + pw_in;

    cout<<"Please enter new user name:";
    cin>>name_new;
    cout<<"Please enter new password:";
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
    ifstream infile(Name);
    infile>>taskData;
    infile.close();

    ofstream outfile(name_new);
    outfile<<taskData;
    outfile.close();

    flag = remove(reinterpret_cast<char*>(&filePath));

    if (flag != 0){cout<<"file not deleted.";} 

    cout<<"account information changed successfully";
    //sleep();
    //system(clear);
}