#include <func.h>
//先fork后open
int main(int argc,char* argv[])
{
    pid_t pid;
    ARGS_CHECK(argc,2);
    int fd;
    char buf[128]={0};
    pid=fork();
    if(0==pid)
    {
        fd=open(argv[1],O_RDWR);
        //子进程
        read(fd,buf,5);
        printf("I am child,%s\n",buf);
        return 1;
    }else{
        fd=open(argv[1],O_RDWR);
        //父进程
        read(fd,buf,5);
        printf("I am parent,%s\n",buf);
        sleep(1);
        return 0;
    }
}

