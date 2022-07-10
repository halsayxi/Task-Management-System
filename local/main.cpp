#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

extern int login(void);
extern void add_user(void);

int main()
{
    string command;
    int choice, status = 2;
    
    cout<<"The system is ready! Input command \"run\" to run the system.\n";
    cin>>command;

    if (command == "run")
    {
        //while循环用于回到原界面
        while(1)
        {
            system("cls");
            cout<<"====welcome to task management system!===="<<endl;
            cout<<"Please choose the sevice you need:\n1.add a new account\n2.login your account\n3.exit\n";
            cin>>choice;
 
            if (choice == 1) add_user();
            else if (choice == 2) status = login();
            else if (choice == 3) break;
            else cout<<"Please input an integer between 1 and 3!" <<endl;
            if (status != 1) sleep(4);
        }
        system("cls");
    }
    return 0;
}