#include <func.h>

int main(int argc,char* argv[])
{
    if(!fork())
    {
        printf("I am child  %d\n",getpid());
        return 0;
    }else{
        printf("I am parent\n");
        pid_t pid=wait(NULL);
        printf("wait success,pid=%d\n",pid);
        return 0;
    }
    return 0;
}

