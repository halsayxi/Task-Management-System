#include <iostream>
#include <queue>
using namespace std;

class user//用户类
{
private:
    struct task//任务类
    {
        char* name;//任务名称
        int type;//任务类型
        int priority;//任务优先级
        int time;//任务预计时间
        int task_id;//唯一的index
    };
    
    char* _id;//用户id名
    int pw_out;//用户密码的密文
    user();
    user(char* id_in,char* pw_in);//初始用户构造 参数为用户输入的用户名和密码
    int get_hash(char* pw_in);//哈希处理密码明文（char*），生成密码密文（int）
    ~user();
    
    //用一个优先级队列维护用户的任务列表
    priority_queue<task> mytask;
    
public:
    void insert_user();//添加账号
    void delete_user();//注销账号
    void print_user();//显示账号信息
    void change_user(int option);//修改账号信息
    void login();//登录账户
    
    void insert_task();//任务录入
    void delete_task();//任务删除
    void print_task(int option);//任务显示
    void remind_task();//任务提醒
    void change_task(int option);//修改任务信息
};


    
