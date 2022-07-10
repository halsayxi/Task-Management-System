#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

extern string get_hash(string);

void change_user(string Name, string Password)
{
    string name_new;
    string pw, pw_in, pw_new, pw_in_new;
    string fileData, taskData, userInfo, userInfo2;
    int location, flag;;
    
    system("cls");
    
    cout<<"Please enter current password:";
    cin>>pw;

    if (pw != Password) {cout<<"Wrong password!"; return;}

    pw_in = get_hash(pw);

    userInfo = Name + pw_in;

    //while循环用于密码输入不符合规范时
    while(1)
    {
        system("cls");
        cout<<"Please enter new user name:";
        cin>>name_new;
        cout<<"Please enter new password:";
        cin>>pw_new;

        if(pw_new.length() != 6) cout<<"The password must be 6-digited";
        else
        {
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

            const char* filePath = Name.data();
            flag = remove(filePath);
 
            if (flag != 0){cout<<"fail to delete the file\n"; return;} 

            cout<<"account information changed successfully\n";
            break;
        }
        sleep(4);
    }
}