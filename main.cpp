//  PPCA日程管理
//  created by halsayxi
#include <getopt.h>
#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <thread>
#include "user.h"
using namespace std;


vector<user> users;//储存所有用户的容器
mutex m; // for multithread use -- lock 
extern queue<string> cmdseq;
extern void print_usage();
extern void input2cmdseq();
extern void clear_queue(queue<string>& q);

// user whx("whx","111");

int main(int argc, char *argv[])
{
    // after login
    user whx("whx","111");

    // for test use(below)
    key key1;
    key1.name = "task0";
    key1.start_time = "2022-00-00 08:00:00";

    task tmp;
    tmp.task_id = 0;
    tmp.name = "task0";
    tmp.type = 0;
    tmp.priority = 0;
    tmp.remind_time = "2022-00-00 08:00:00";
    tmp.start_time = "2022-00-00 08:00:00";
    tmp.flag = false;
    tmp.remind_flag = false;
    // for test use(above)

    whx.mytask.insert(make_pair(key1, tmp));
    print_usage();  // print usage string
    printf("Please run the command first!\n > ./MyCalendar run\n");
    if(cmdseq.size()!=0)
    clear_queue(cmdseq);

    thread task_arrangement(process_all, ref(whx));
    thread task_scanning(&user::remind_all, &whx);

    task_arrangement.join();
    task_scanning.join();
    // while (1)
    // {
    //     if(cmdseq.size()==0)
    //     {
    //         printf("请输入\nshowtask || donetask || deltask || addtask || exit\n > ");
    //         input2cmdseq();
    //     }
    //     cmd=cmdseq.front();
    //     cmdseq.pop();
    //     task_process(whx,cmd);
    // }
    return 0;
}

