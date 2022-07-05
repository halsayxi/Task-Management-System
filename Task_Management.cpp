#ifndef TASK
#define TASK
#include "user.h"
#endif
// accomplish the functions in class user
int task_process(user usr, string cmd)
{
    if (cmd == "exit") return 1;
    if (cmd == "showtask") printf("showtask\n"); // usr.print_task()
    if (cmd == "donetask") printf("donetask\n"); // usr.change_task
    if (cmd == "deltask") printf("deltask\n"); // usr.delete_task()
    if (cmd == "addtask") printf("addtask\n"); // usr.insert_task()
    return 0;
}
