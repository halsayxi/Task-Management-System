#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "user.h"
using namespace std;

mutex m;
int debug = 0;
extern int login(void);
extern void add_user(void);
extern void print_usage();
extern void DelLineData(string fileName);
extern void ReadLineData(string fileName, int lineNum, string& command);
int main(int argc, char *argv[])
{
    string command;
    int choice, status = 2;
    char opt;
    while (((opt = getopt(argc, argv, "hd")) != -1))
    {
        switch(opt)
        {
            case 'h':
            {
                print_usage();
                return 1;
            }
            case 'd':
            {
                debug = 1; break;// Debug mode is activated
            }
            default:debug = 0;
        }
    }
    if (debug == 1)
    {
        cout << "\nTest Mode is Activated!\n";
        sleep(3);
    }
    cout<<"The system is ready! Input command \"run\" to run the system.\n" << "> ";
    if (debug == 0) cin>>command;
    else
    {
        ifstream testfile("testfile.txt");
        if (!testfile.is_open()) return -1;
        testfile >> command;
        testfile.close();
        DelLineData("testfile.txt");
        cout << command;
    }
    if (command == "run")
    {
        //while循环用于回到原界面
        while(1)
        {
            if (debug == 0) system("clear");
            cout<<"\n====Welcome to task management system!===="<<endl;
            cout<<"Please choose the sevice you need:\n1.add a new account\n2.login your account\n3.exit\n" << "> ";
            if (debug == 0) cin>>choice;
            else
            {
                ifstream testfile("testfile.txt");
                if (!testfile.is_open()) return -1;
                testfile >> choice;
                testfile.close();
                DelLineData("testfile.txt");
                cout << choice;
            }
            if (choice == 1) add_user();
            else if (choice == 2) status = login();
            else if (choice == 3) break;
            else cout<<"Please input an integer between 1 and 3!" <<endl;
            if (status == 0) sleep(4);
        }
        if (debug == 0) system("clear");

    }
    return 0;
}
