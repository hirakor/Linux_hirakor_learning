#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("before %d is coming\n",signum);
    sleep(3);
    printf("after %d is coming\n",signum);
}

int main(int argc,char* argv[]){
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;//信号处理行为函数
    act.sa_flags=SA_SIGINFO|SA_NODEFER;
    ret=sigaction(SIGINT,&act,NULL);//  act指针是传入参数
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

