#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;

void delete_user(string Name, string Password)
{
    string fileData, userInfo;
    int location;
    string filePath = "C:\\Users\\86177\\Desktop\\code\\user";
    filePath = filePath + Name;
    
    userInfo = Name + Password;

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

    remove(reinterpret_cast<char*> (&filePath));

    cout<<"account deleted successfully!";
    //sleep();
    //system(clear);
}