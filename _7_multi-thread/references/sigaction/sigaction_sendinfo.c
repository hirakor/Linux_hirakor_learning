#include <func.h>
void sigFunc(int signum,siginfo_t *p,void* p1)
{
    printf("%d is coming,send signal uid=%d,send pid=%d\n",signum,p->si_uid,p->si_pid);
}
int main()
{
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;//信号处理行为函数
    act.sa_flags=SA_SIGINFO;
    ret=sigaction(SIGINT,&act,NULL);
    while(1);
    return 0;
}

