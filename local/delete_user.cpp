#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>

using namespace std;

void delete_user(string Name, string Password)
{
    string fileData, userInfo;
    int location, flag;
    
    system("cls");
    
    userInfo = Name + Password;

    //删除user中用户信息
    ifstream in("users");
    if (!in) {cerr<<"error! Unable to open the file."; return;}
    in>>fileData;
    location = fileData.find(userInfo,0);
    fileData.erase(location, userInfo.length());
    in.close();

    ofstream out("users");
    if (!out) {cerr<<"error! Unable to open the file."; return;}
    out<<fileData;
    out.close();

    //删除用户存放任务的文件
    const char* filePath = Name.data();
    flag = remove(filePath);

    if (flag != 0) {cout<<"fail to delete the file\n"; return;}

    cout<<"account deleted successfully!\n";
}