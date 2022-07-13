#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
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
    // promise<int> promiseObj;
    // future<int> futureObj = promiseObj.get_future(); 
    int exit_flag = 0;
    user usr(name, pw);
    usr.load_task();
    thread task_arrangement(process_all, ref(usr), ref(exit_flag));
    // thread task_scanning(&user::remind_all, &usr);
    thread task_scanning(&user::remind_all, &usr, ref(exit_flag));
    // int exit_flag = futureObj.get();
    // cout << "exit_flag:" << exit_flag << endl;

    task_arrangement.join();
    task_scanning.join();
    if(cmdseq.size()!=0) clear_queue(cmdseq);
    // if (exit_flag == 1) return 1;
    // else return 0;
    return;
}
