#include <func.h>
void sigFunc(int signum)
{
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    printf("after sleep %d is coming\n",signum);
}
//2号和3号信号都要捕捉
int main()
{
    signal(SIGINT,sigFunc);//内核调用我们设置的信号处理行为函数
    signal(SIGQUIT,sigFunc);//设定3号信号
    while(1);
    return 0;
}

