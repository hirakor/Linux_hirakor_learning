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
    int ret;
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    char buf[128]={0};
    socklen_t addrlen=sizeof(struct sockaddr);
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr *)&client,&addrlen);
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    printf("%s\n",buf);
    sendto(socketFd,"I am hungry",11,0,(struct sockaddr *)&client,sizeof(client));
    close(socketFd);

    return 0;
}

