#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;

extern string get_hash(string);

void add_user()
{
    string name;
    string pw, pw2, pw_in;
    
    while(1)
    {
        cout<<"Please enter your user name:";
        cin>>name;
        cout<<"Please enter the new 6-digit password:";
        cin>>pw;
        cout<<"confirm your password:";
        cin>>pw2;

        if (pw == pw2 && pw.length() == 6) 
        {
            cout<<"a new account created successfully!";
            break;
        }
        else cout<<"Wrong password. Failed to create a new account.";
    }

    pw_in = get_hash(pw);
    
    ofstream out("users",ofstream::app);
    if (!out) {cerr<<"error! Unable to create the file."; return;}
    out<<name<<pw_in;
    out.close();

    ofstream outfile(name);  //用于存放任务
    if (!outfile) {cerr<<"error! Unable to create the file."; return;}
    outfile.close();

    cout<<"file created successfully!";

}