#include <func.h>

void sigfunc(int signum)
{
    printf("%d is coming\n",signum);
}
int main()
{
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,sigfunc);
    printf("Hello world\n");
    while(1);
    return 0;
}
