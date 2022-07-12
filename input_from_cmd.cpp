#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

void print_usage()
{
    printf("Utilities\n");
}

queue<string> cmdseq;
void input2cmdseq()
{
    string tmp = "";
    char c;
    while(1)
    {
        cin >> tmp;
        cmdseq.push(tmp);
        c = getchar();
        if (c == '\n')
        {
            break;
        }
    }
}

void clear_queue(queue<string>& q)
{
    queue<string> empty;
    swap(empty, q);
}


