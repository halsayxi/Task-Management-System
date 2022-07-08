#include <delete_user.h>

void delete_user(string Name, string Password)
{
    string fileData, userInfo;
    int location;
    
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

    cout<<"账号注销成功！";
    //sleep();
    //system(clear);
}