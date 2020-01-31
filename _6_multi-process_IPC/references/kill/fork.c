#include <func.h>

int main(int argc,char* argv[])
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        printf("I am child,mypid=%d,ppid=%d\n",getpid(),getppid());
        while(1);
        return 0;
    }else{
        printf("I am parent,child pid=%d,mypid=%d\n",pid,getpid());
        while(1);
        sleep(1);
    }
    return 0;
}

