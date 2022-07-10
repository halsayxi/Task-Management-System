//  PPCA日程管理
//  created by halsayxi
#include <getopt.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstring>
#include <thread>
#include "user.h"
using namespace std;
mutex m;
vector<user> users;//储存所有用户的容器
extern void print_usage();
extern queue<string> cmdseq;
extern void input2cmdseq();
extern void clear_queue(queue<string>& q);


int main(int argc, char *argv[])
{
    // after login
    user whx("whx","111");
    
    print_usage();  // print usage string
    printf("Please run the command first!\n > ./MyCalendar run\n");
    
    //任务加载，先读取文件中的内容并输入到map中
    whx.load_task();
    
    /*    测试Periodic_Scanning    */
    thread task_arrangement(process_all, ref(whx));
    thread task_scanning(&user::remind_all, &whx);

    task_arrangement.join();
    task_scanning.join();
    
    /*    测试Task_Management    */
    
    //执行命令行操作
    if(cmdseq.size()!=0)
    clear_queue(cmdseq);
    
    return 0;
}

