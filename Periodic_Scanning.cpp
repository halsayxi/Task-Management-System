#ifndef SCAN
#define SCAN
#include "user.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <cstring>
#include <stdio.h>
#include <queue>
#include <map>
#include <ctime>
#endif
using namespace std;
extern mutex m; // for multithread use -- lock
void user::remind_task()//任务提醒
{
    /*获取当前时间*/
    
    time_t nowtime;//创建一个time_t类型的变量
    struct tm* p;//创建一个新时间结构体指针 p
    time(&nowtime);//使用该函数可以得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
    p=localtime(&nowtime);//调用本地时间函数p=localtime（time_t* nowtime）将nowtime变量中的日历时间转化为本地时间，存入到指针为p的时间结构体中

    string now_time="2022-00-00 00:00:00";
    string yyyy=std::to_string(p->tm_year+1900);
    string mm=std::to_string(p->tm_mon+1);
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
    
    
    /*根据当前时间遍历map，提醒所有提醒时间已经到达的日程*/
    try
    {
        unique_lock<mutex> g2(m,try_to_lock);
        if (g2.owns_lock())
        {
            auto i=user::mytask.begin();//遍历指针
            
            while(i!=user::mytask.end())
            {
                if(i->second.flag==true || i->second.remind_flag==true)   // if flag==true,the task is finished
                {
                    i++;
                    continue;
                }
                if(i->second.remind_time<now_time)
                {
                    cout<<"Schedule reminder——\n"<<"Your schedule "<<i->second.name<<" will start at "<<i->second.start_time<<"\nCurrent time: "<< now_time <<endl;
                    i->second.remind_flag=true;
                }
                i++;
            }
        }
        else
        {
            cout<<"\nLock Error when add task!\n";
        }
        g2.unlock();

    }
    catch(const std::exception& e)
    {
        cout<<"\nmytask is empty!\n";
    }
}
// void user::remind_all()
void user::remind_all(int &exit_flag)
{
    while(1)
    {
        remind_task();
        if (exit_flag == 1) return;
        sleep(5);
    }
}
