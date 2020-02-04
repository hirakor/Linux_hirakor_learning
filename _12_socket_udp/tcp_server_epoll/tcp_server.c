#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    //初始化一个socket，有一个缓冲区
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);//端口激活
    int new_fd;//用来保存新建连接
    struct sockaddr_in client;//从内核拿出对方的socket信息
    
    char buf[1000]={0};
    int epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.data.fd=STDIN_FILENO;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdNum;
    int i;
    while(1){
        readyFdNum=epoll_wait(epfd,evs,3,-1);
        for(i=0;readyFdNum>i;i++){
            if(evs[i].data.fd==socketFd){     //新用户连接
                bzero(&client,sizeof(client));
                socklen_t len=sizeof(client);
                new_fd=accept(socketFd,(struct sockaddr *)&client,&len);
                ERROR_CHECK(new_fd,-1,"accept");
                printf("client ip=%s,client port=%d\n",\
                       inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                event.data.fd=new_fd;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
            if(evs[i].data.fd==new_fd){
                bzero(buf,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf),0);
                if(!ret){   //对方断开了,让它再连
                    printf("byebye\n");
                    event.data.fd=new_fd;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
                    close(new_fd);        
                }else{
                    printf("%s\n",buf);
                }
            }
            if(evs[i].data.fd==STDIN_FILENO){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(new_fd,buf,strlen(buf)-1,0);
            }
        }
    }
end:
    close(new_fd);
    close(socketFd);
    return 0;
}

