#include <func.h>

int main(int argc,char* argv[])
{
    pid_t pid;
    char *p=(char*)malloc(20);
    strcpy(p,"hello");
    pid=fork();
    if(0==pid)
    {
        //子进程
        printf("I am child,%s\n",p);
        return 0;
    }else{
        //父进程
        printf("I am parent,%s\n",p);
        strcpy(p,"world");
        printf("I am parent,%s\n",p);
        sleep(1);
        return 0;
    }
}

