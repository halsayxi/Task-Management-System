#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <conio.h>

using namespace std;

extern string get_hash(string);

void print_user(string Name, string Password)
{
    string pw, pw_in, pw_in2;
    char ch;

    system("cls");

    cout<<"Please enter the password:";
    while ((ch=_getch())!=13)  //回车键ASCII码是13
    {
        pw+=ch;
        cout<<"*";
    }
    cout<<endl;

    pw_in = get_hash(Password);
    pw_in2 = get_hash(pw);
    
    if (pw_in != pw_in2) {cout<<"Wrong password!"; return;}
    cout<<"Username:"<<Name<<endl;
    cout<<"Password:"<<Password<<endl;
}