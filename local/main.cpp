#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
using namespace std;

extern void login(void);
extern void add_user(void);

int main()
{
    int choice;
    
    while(1)
    {
        cout<<"====welcome to task management system!===="<<endl;
        //sleep()
        cout<<"Please choose the sevice you need:\n1.add a new account\n2.login your account\n3.exit\n";
        cin>>choice;

        if (choice == 1) add_user();
        else if (choice == 2) login();
        else if (choice == 3) break;
        else cout<<"Please input an integer between 1 and 3!" <<endl;
    }

    return 0;
}