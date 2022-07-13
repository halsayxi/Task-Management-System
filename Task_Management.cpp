#include "user.h"
using namespace std;

extern mutex m;
extern void print_usage();

void task_management(string name,string pw)
{

    int exit_flag = 0;
    user usr(name, pw);
    usr.load_task();
    thread task_arrangement(process_all, ref(usr), ref(exit_flag));
    thread task_scanning(&user::remind_all, &usr, ref(exit_flag));

    task_arrangement.join();
    task_scanning.join();
    return;
}
