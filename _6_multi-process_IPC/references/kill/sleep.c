#include <func.h>
void sigFunc(int signum)
{
}
int main()
{   
    signal(SIGALRM,sigFunc);
    alarm(3);
    pause();
    return 0;
}

