#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>

using namespace std;

void print_user(string Name, string Password)
{
    string pw, pw_in;   
    string userInfo, fileData;
    
    system("cls");

    cout<<"Please enter the password!";
    cin>>pw;

    if (pw != Password) {cout<<"Wrong password!"; return;}

    cout<<"Username:"<<Name<<endl;
    cout<<"Password:"<<Password<<endl;
}