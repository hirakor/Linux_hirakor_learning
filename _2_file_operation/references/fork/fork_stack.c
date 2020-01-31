#include <func.h>

int main(int argc,char* argv[])
{
    pid_t pid;
    int i=10;
    pid=fork();
    if(0==pid)
    {
        //子进程
        printf("I am child,&i=%p,i=%d\n",&i,i);
        return 0;
    }else{
        //父进程
        printf("I am parent,&i=%p,i=%d\n",&i,i);
        i=5;
        printf("I am parent,&i=%p,i=%d\n",&i,i);
        sleep(1);
        return 0;
    }
}

