#include <func.h>

int main(int argc,char* argv[])
{
    pid_t pid;
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    char buf[128]={0};
    pid=fork();
    if(0==pid)
    {
        //子进程
        read(fd,buf,5);
        printf("I am child,%s\n",buf);
        return 0;
    }else{
        //父进程
        read(fd,buf,5);
        printf("I am parent,%s\n",buf);
        sleep(1);
        return 0;
    }
}

