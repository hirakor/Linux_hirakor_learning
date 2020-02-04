#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero (&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    //客户端一定要先sendto
    char buf[128]={0};
    const char *p="I am JISOO";
   // socklen_t addrlen=sizeof(struct sockaddr);
    sendto(socketFd,p,strlen(p),0,(struct sockaddr *)&ser,sizeof(ser));
    recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
    printf("%s\n",buf);
    close(socketFd);

    return 0;
}

