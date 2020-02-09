#include "process_pool.h"

int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        printf("usage ./process_pool_server IP PORT PROCESS_NUM\n");
        return -1;
    }
    int processNum=atoi(argv[3]);//进程数目
    process_data_t *pData=(process_data_t*)calloc(processNum,sizeof(process_data_t));
    make_child(pData,processNum);//创建子进程并初始化数据结构
    int socketFd;
    //为了实现socket，bind,listen
    tcp_init(&socketFd,argv[1],argv[2]);
    //使用epoll监控socketFd
    int epfd=epoll_create(1);
    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(processNum+1,sizeof(struct epoll_event));
    event.events=EPOLLIN;
    event.data.fd=socketFd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    int i;
    //监控每一个子进程管道对端
    for(i=0;i<processNum;i++)
    {
        event.data.fd=pData[i].fd;
        epoll_ctl(epfd,EPOLL_CTL_ADD,pData[i].fd,&event);
    }
    int readyFdNum,newFd,j;
    struct sockaddr_in client;
    char childBusyFlag=0;
    while(1)
    {
        readyFdNum=epoll_wait(epfd,evs,processNum+1,-1);
        for(i=0;i<readyFdNum;i++)
        {
            //有客户端请求
            if(evs[i].data.fd==socketFd)
            {
                bzero(&client,sizeof(client));
                socklen_t len=sizeof(client);
                newFd=accept(socketFd,(struct sockaddr *)&client,&len);
                ERROR_CHECK(newFd,-1,"accept");
                printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                //找非忙碌的子进程，然后把任务派给她
                for(j=0;j<processNum;j++)
                {
                    if(0==pData[j].busy)
                    {
                        sendFd(pData[j].fd,newFd);//发newFd给子进程
                        printf("main process give %d task to %d\n",newFd,pData[j].pid);
                        pData[j].busy=1;//设置为忙碌
                        break;
                    }
                }
                close(newFd);//减少引用计数
            }
            //子进程不忙碌通知父进程
            for(j=0;j<processNum;j++)
            {
                if(evs[i].data.fd==pData[j].fd)//判断是哪一个子进程
                {
                    read(pData[j].fd,&childBusyFlag,1);//把数据读出来
                    pData[j].busy=0;//状态改为非忙碌
                    printf("%d is not busy\n",pData[j].pid);//打印协助理解
                    break;
                }
            }
        }
    }
    return 0;
}

