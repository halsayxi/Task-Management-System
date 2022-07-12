#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <thread>
#include "user.h"
using namespace std;

extern mutex m;
extern void print_usage();
extern queue<string> cmdseq;
extern void input2cmdseq();
extern void clear_queue(queue<string>& q);

void task_management(string name,string pw)
{
    // cout << "0\n";
    user usr(name, pw);
    //print_usage();  // print usage string
    // cout << "1\n";
    usr.load_task();
    // cout << "2\n";
    thread task_arrangement(process_all, ref(usr));
    thread task_scanning(&user::remind_all, &usr);

    task_arrangement.join();
    task_scanning.join();
    if(cmdseq.size()!=0) clear_queue(cmdseq);
    return;
}
