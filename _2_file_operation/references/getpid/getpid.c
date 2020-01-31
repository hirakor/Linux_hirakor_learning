#include <func.h>

int main(int argc,char* argv[])
{
    pid_t pid,ppid;
    pid=getpid();
    ppid=getppid();
    printf("mypid=%d,ppid=%d\n",pid,ppid);
    while(1);
    return 0;
}

