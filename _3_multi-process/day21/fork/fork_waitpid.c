#include <func.h>

int main(int argc,char* argv[])
{
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child  %d\n",getpid());
        return 0;
    }else{
        printf("I am parent\n");
        pid=waitpid(pid,NULL,WNOHANG);
        printf("wait success,pid=%d\n",pid);
        return 0;
    }
    return 0;
}

