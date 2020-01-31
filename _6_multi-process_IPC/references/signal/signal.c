#include <func.h>
void sigFunc(int signum)
{
    printf("%d is coming,ok\n",signum);
}
int main()
{
    signal(SIGINT,sigFunc);//内核调用我们设置的信号处理行为函数
    while(1);
    return 0;
}

