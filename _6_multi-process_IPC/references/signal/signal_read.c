#include <func.h>
void sigFunc(int signum)
{
    printf("%d is coming,ok\n",signum);
}
int main()
{
    signal(SIGINT,sigFunc);//内核调用我们设置的信号处理行为函数
    char buf[128]={0};
    read(STDIN_FILENO,buf,sizeof(buf));
    printf("%s\n",buf);
    return 0;
}

