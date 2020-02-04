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
    ret=connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));
    ERROR_CHECK(ret,-1,"connect");
    char buf[1000]={0};
    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        ret=select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(ret>0)
        {
            if(FD_ISSET(socketFd,&rdset))
            {
                bzero(buf,sizeof(buf));
                ret=recv(socketFd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("byebye\n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(socketFd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(socketFd);
    return 0;
}
