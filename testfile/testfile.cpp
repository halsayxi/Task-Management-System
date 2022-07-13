#include <stdlib.h>
#include <iostream>
#include <unistd.h>
int main()
{
    system("rm testfile.txt");
    system("cp testfile.origin testfile.txt");
    char* argv[]={"./test", "-d", NULL};
    execv("./test", argv);
    return 0;
}