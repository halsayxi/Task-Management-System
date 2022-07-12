#ifndef USER_H
#define USER_H

#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <mutex>
#include <unistd.h>
using namespace std;


struct task//任务类
{
    string task_id;//唯一的index
    string name;//任务名称
    int type;//任务类型 缺省值为生活
    int priority;//任务优先级 缺省值为低
    string remind_time;//提醒时间
    string start_time;//启动时间
    bool flag;//是否已完成 完成为true
    bool remind_flag;//是否已提醒 已提醒为true//不存入文件
};


struct key//因为任务id具有唯一性，故将这个属性作为任务在map中存储的键值
{
    
    string task_id;//任务id

    bool operator < (const key &key1) const
    {
        return task_id < key1.task_id;
    }
    bool operator > (const key &key1) const
    {
        return task_id > key1.task_id;
    }
    bool operator == (const key &key1) const
    {
        return task_id == key1.task_id;
    }

};


class user//用户类
{
private:
    //用一个队列维护用户的任务列表 根据remind_time排序
    int count=0;
    map<key,task> mytask;
    
    string _id;//用户id名
    int pw_out;//用户密码的密文
    int get_hash(char* pw_in);//哈希处理密码明文（char*），生成密码密文（int）
    
public:
    user(){};
    user(string id_in,string pw_in)//初始用户构造 参数为用户输入的用户名和密码
    {
        _id=id_in;
    };
    ~user(){};

    void insert_user();//添加账号
    void delete_user();//注销账号
    void print_user();//显示账号信息
    void change_user(int option);//修改账号信息
    
    void insert_task();//任务录入
    void delete_task();//任务删除
    void print_task();//任务显示
    void remind_all();
    void remind_task();//任务提醒
    void done_task();//修改任务信息
    void load_task();//任务加载
    void exit_task();//退出
};

// Account_Management.cpp
user login(int &flag);//登录账户

// Task_Management.cpp
int task_process(user& usr, string task);

void process_all(user& usr);
#endif
