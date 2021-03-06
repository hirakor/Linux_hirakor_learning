#include "process_pool.h"

int make_child(process_data_t* p,int processNum)
{
    int sockFds[2];
    int i;
    pid_t pid;
    for(i=0;i<processNum;i++)
    {
        int ret=socketpair(AF_LOCAL,SOCK_STREAM,0,sockFds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(0==pid)
        {
            close(sockFds[0]);
            child_handle(sockFds[1]);
        }
        close(sockFds[1]);
        //只有父进程在走for循环
        p[i].pid=pid;
        p[i].fd=sockFds[0];
        p[i].busy=0;
    }
    return 0;
}

int child_handle(int fds)
{
    int newFd;
    char finishFlag=0;
    while(1)
    {
        //拿到父进程分配的任务
        recvFd(fds,&newFd);
        printf("I am child,get %d\n",newFd);
        trans_file(newFd);//发送文件给客户端
        close(newFd);
        printf("finish task\n");
        write(fds,&finishFlag,1);//通知父进程我完成任务了
    }
    exit(0);
}

