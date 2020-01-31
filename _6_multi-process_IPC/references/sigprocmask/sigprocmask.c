#include <func.h>

int main()
{
    sigset_t mask;
    sigemptyset(&mask);
    sigfillset(&mask);//防止所有信号触及关键代码
    int ret=sigprocmask(SIG_BLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    printf("before sleep\n");
    sleep(5);
    printf("after sleep\n");
    ret=sigprocmask(SIG_UNBLOCK,&mask,NULL);
    printf("programme over\n");
    return 0;
}

