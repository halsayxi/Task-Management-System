#ifndef SCAN
#define SCAN
#include "user.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>
#include <ctime>
#endif
using namespace std;

void user::remind_task()//任务提醒
{
    /*获取当前时间*/
    
    time_t nowtime;
    //创建一个time_t 类型的变量nowtime
    struct tm* p;
    //创建一个新时间结构体指针 p
    time(&nowtime);
    //使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
    p=localtime(&nowtime);
    //由于此时变量nowtime中的系统时间值为日历时间，我们需要调用本地时间函数p=localtime（time_t* nowtime）将nowtime变量中的日历时间转化为本地时间，存入到指针为p的时间结构体中。

    string now_time="2022-00-00 00:00:00";
    string yyyy=std::to_string(p->tm_year+1900);
    string mm=std::to_string(p->tm_mon);
    string dd=std::to_string(p->tm_mday);
    string hh=std::to_string(p->tm_hour);
    string ff=std::to_string(p->tm_min);
    now_time[0]=yyyy[0];
    now_time[1]=yyyy[1];
    now_time[2]=yyyy[2];
    now_time[3]=yyyy[3];
    if(p->tm_mon>=10)
    {
        now_time[5]=mm[0];
        now_time[6]=mm[1];
    }
    else
    {
        now_time[6]=mm[0];
    }
    if(p->tm_mday>=10)
    {
        now_time[8]=dd[0];
        now_time[9]=dd[1];
    }
    else
    {
        now_time[9]=dd[0];
    }
    if(p->tm_hour>=10)
    {
        now_time[11]=hh[0];
        now_time[12]=hh[1];
    }
    else
    {
        now_time[12]=hh[0];
    }
    if(p->tm_min>=10)
    {
        now_time[14]=ff[0];
        now_time[15]=ff[1];
    }
    else
    {
        now_time[15]=ff[0];
    }
    
    /*获取最小的提醒时间*/
    
    auto i=user::mytask.begin();//遍历指针
    string k=i->second.remind_time;//最小的remind_time
    auto j=user::mytask.begin();//指向需要被提醒的任务
    
    while(i!=user::mytask.end())
    {
        if(i->second.flag || i->second.remind_flag)
        {
            i++;
            continue;
        }
        if(i->second.remind_time<k)
        {
            k=i->second.remind_time;
            j=i;
        }
        i++;
    }

    task tmp_task=j->second;
    string tmp_time=tmp_task.remind_time;
    
    if(now_time>=tmp_time)
    {
        cout<<"日程提醒："<<tmp_task.name<<endl;
        tmp_task.remind_flag=true;
    }
}
