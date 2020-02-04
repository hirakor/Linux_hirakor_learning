#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);

    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);

    int ret;
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);

    int new_fd;
    struct sockaddr_in client;  //从内核中拿出对方的socket信息
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(client);
    new_fd=accept(socketFd,(struct sockaddr *)&client,&len);
    ERROR_CHECK(new_fd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    
    char buf[1000]={0};
    fd_set rdset;
    int readyFdNum;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(new_fd,&rdset);
        readyFdNum=select(new_fd+1,&rdset,NULL,NULL,NULL);
        if(readyFdNum>0){
            if(FD_ISSET(new_fd,&rdset)){
                bzero(buf,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf),0);
                if(!ret){
                    printf("byebye\n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(new_fd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(new_fd);
    close(socketFd);

    return 0;
}

