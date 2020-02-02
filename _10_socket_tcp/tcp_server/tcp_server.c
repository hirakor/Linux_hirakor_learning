#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    int socketFd;   //初始化一个socket，有一个缓冲区
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");  //生成一个套接口描述符
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);    //端口激活

    int new_fd; //用来保存新建连接
    struct sockaddr_in client;  //从内核中拿出对方的socket信息
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(client);
    new_fd=accept(socketFd,(struct sockaddr *)&client,&len);
    ERROR_CHECK(new_fd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),\
           ntohs(client.sin_port));
    char buf[128]={0};
    recv(new_fd,buf,sizeof(buf),0);
    printf("I am server ,gets=%s\n",buf);

    return 0;
}

