#include <func.h>

void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("before sleep %d is coming,ok\n",signum);
    sleep(3);
    printf("after sleep %d is coming,ok\n",signum);
}

int main(int argc,char* argv[]){
//    signal(SIGINT,sigFunc);   //内核调用我们设置的信号处理行为函数
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;//信号处理行为函数
    act.sa_flags=SA_SIGINFO;
    ret=sigaction(SIGINT,&act,NULL);//act指针
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

