#include <func.h>
//mask 是保护推出进程
void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("    before %d is coming\n",signum);
    sleep(3);
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);// 从内核把挂着的信号拿出来
    if(sigismember(&pending,SIGQUIT)){
        printf("    SIGQUIT is pending\n");
    }else{
        printf("    SIGQUIT is not pending\n");
    }
    printf("    after %d is coming\n",signum);
}

int main(int argc,char* argv[]){
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;//信号处理行为函数
    act.sa_flags=SA_SIGINFO;
    sigaddset(&act.sa_mask,SIGQUIT);//  阻塞3号信号
    ret=sigaction(SIGINT,&act,NULL);//  act指针是传入参数
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

