#ifndef INPUT
#define INPUT

#include "user.h"

#endif
extern queue<string> cmdseq; 
void print_usage()
{
    printf("Utilities\n");
}

void input2cmdseq() {
    string tmp = ""; 
    char c;
    while(1) {
        cin >> tmp;
        cmdseq.push(tmp);
        c = getchar();
        if (c == '\n') {
            break;
        }
    }
}





