//  PPCA日程管理
//  created by halsayxi
#include <getopt.h>
#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include "user.h"
using namespace std;

vector<user> users;//储存所有用户的容器
extern void print_usage();
extern queue<string> cmdseq;
extern void input2cmdseq();

//多线程处理
int main(int argc, char *argv[])
{
    char opt;
    int flag;
    flag = 0;

    while (((opt = getopt(argc, argv, "h")) != -1) || (argc == 1))
    {
        print_usage();  // print usage string
        return 0;
    }
    
    if (!strcmp(argv[1], "run"))
    {
        user usr;
        while(flag != 1)
        {
            usr = login(flag);
        }
         
        while(1)
        {
            printf("> ");
            input2cmdseq();
            if (cmdseq.size() == 0) return 0;
            string cmd = cmdseq.front();
            cmdseq.pop();
            if (task_process(usr, cmd) == 1) return 1;
            // return 0;
        }
    }
    else printf("Please run the following command first!\n > ./MyCalendar run\n");
    return 0;
}
