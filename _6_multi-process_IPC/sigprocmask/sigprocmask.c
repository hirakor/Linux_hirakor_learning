#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1){
    sleep(5);
}
int main(int argc,char* argv[]){
    sigset_t mask;
    sigemptyset(&mask);
    sigfillset(&mask); // 防止所有信号触及关键代码
    
    int ret=sigprocmask(SIG_BLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO;
    sigaddset(&act.sa_mask,SIGINT);
    
    sigpending(&mask);
    if(sigismember(&mask,SIGINT)){
        printf("SIGINT is pending\n");
    }else{
        printf("SIGINT is not pending\n");
    }

    ret=sigprocmask(SIG_UNBLOCK,&mask,NULL);//
    ERROR_CHECK(ret,-1,"sigprocmask");
    printf("programme over\n");
    return 0;
}

