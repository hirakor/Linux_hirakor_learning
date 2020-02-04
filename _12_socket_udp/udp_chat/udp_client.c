#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    //初始化一个socket，有一个缓冲区
    socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    //客户端一定要先sendto
    const char *p="1";
    sendto(socketFd,p,strlen(p),0,(struct sockaddr*)&ser,sizeof(ser));
    char buf[1000]={0};
    fd_set rdset;
    int readyFdNum;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        readyFdNum=select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(readyFdNum>0)
        {
            if(FD_ISSET(socketFd,&rdset))
            {
                bzero(buf,sizeof(buf));
                //针对客户端我们知道服务器是谁
                recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(buf,sizeof(buf));
                //读到的内容发送给客户端
                read(STDIN_FILENO,buf,sizeof(buf));
                sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,sizeof(struct sockaddr));
            }
        }
    }
    close(socketFd);
}
