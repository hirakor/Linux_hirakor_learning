#include <func.h>
int print()
{
    exit(1);//子进程在这里终止
}
int main(int argc,char* argv[])
{
    if(!fork())
    {
        printf("I am child  %d\n",getpid());
        print();
        printf("I am child after print\n");
        return 0;
    }else{
        printf("I am parent\n");
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("child exit code=%d\n",WEXITSTATUS(status));
        }
        return 0;
    }
}

