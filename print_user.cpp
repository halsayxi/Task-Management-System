#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

extern string get_hash(string);

void print_user(string Name, string Password)
{
    string pw, pw_in, pw_in2;

    system("clear");

    cout<<"Please enter the password:";
    system("stty -echo");
    cin>>pw;
    system("stty echo");
    cout<<endl;
    
    pw_in = get_hash(Password);
    pw_in2 = get_hash(pw);
    
    if (pw_in != pw_in2) {cout<<"Wrong password!"; return;}
    cout<<"Username:"<<Name<<endl;
    cout<<"Password:"<<Password<<endl;
}
