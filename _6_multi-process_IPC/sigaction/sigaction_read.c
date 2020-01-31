#include <func.h>

void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("%d is coming,ok\n",signum);
}

int main(int argc,char* argv[])
{
//    signal(SIGINT,sigFunc);   //内核调用我们设置的信号处理行为函数
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;//信号处理行为函数
    act.sa_flags=SA_SIGINFO;
    ret=sigaction(SIGINT,&act,NULL);
    //阻塞在read系统调用
    char buf[128]={0};
    read(0,buf,sizeof(buf));
    //while(1);
    return 0;
}

