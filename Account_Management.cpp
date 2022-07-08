#ifndef ACCOUNT
#define ACCOUNT

#include "user.h"

#endif
user login(int &flag)
{
    string account, password;
    account = "";
    password = "";
    printf("please enter your account:");
    cin >> account;
    printf("please enter your password:");
    cin >> password;

    if ((account != "") && (password != ""))
    // if (authorize())  // authorize the account and password
    {
        cout << "=============Welcome" << " " <<account << "!==============\n";
        user usr(account, password); // initialize a user object
        flag = 1;
        return usr;
    }
    else
    {
        printf("Error!Please enter your account and password again!");
        user usr;
        flag = 0;
        return usr;
    }
    
}

