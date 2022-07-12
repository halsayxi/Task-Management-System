#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <conio.h>

using namespace std;

void delete_user(string Name, string Password)
{
    string pw;
    string fileData;
    char ch;
    int flag;
    
    system("cls");

    cout<<"Please enter current password:";
    while ((ch=_getch())!=13)  //回车键ASCII码是13
    {
        pw+=ch;//string对象重载了+=
        cout<<"*";
    }
    cout<<endl;

    if (pw != Password) {cout<<"Wrong password!"; return;}

    //删除user中用户信息
    ifstream in("users");  
    if (!in) {cerr<<"No account existed! Please register an account first.\n"; return;}
    ofstream out("tmp");

    while(getline(in,fileData))//得到原文件中一行的内容
    {
        if (!fileData.compare(Name))//比较原文件每一行的内容和要删除的是否一致，一致就跳过
        {
            getline(in,fileData);
            continue;
        }
        out<<fileData<<"\n";//不一致的内容写到中间文件中，注意换行
    }

    in.close();//关闭流
    out.close();
    fstream outfile("users", ios::out);
    fstream infile("tmp", ios::in);
    while(getline(infile, fileData)) //将中间文件的内容写到原文件（覆盖）
    {
    outfile<<fileData<<"\n";
    }
    outfile.close();//关闭流
    infile.close();

    const char* path = "tmp";
    remove(path);//删除tmp

    //删除用户存放任务的文件
    const char* filePath = Name.data();
    flag = remove(filePath);

    if (flag != 0) {cout<<"fail to delete the file\n"; return;}

    //删除“用户名+count”文件
    string filename = Name + "count";
    const char* filePath_2 = filename.data();
    flag = remove(filePath_2);

    if (flag != 0) {cout<<"fail to delete the file\n"; return;}

    cout<<"account deleted successfully!\n";
}