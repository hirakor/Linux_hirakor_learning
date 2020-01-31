#include <func.h>

void sigfunc(int signum)
{
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    printf("after sleep %d is coming\n",signum);
}
int main()
{
    signal(SIGINT,sigfunc);
    signal(SIGQUIT,sigfunc);
    printf("Hello world\n");
    while(1);
    return 0;
}
