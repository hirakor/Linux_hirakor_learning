#include <func.h>

int main(int argc,char **argv){
    ARGS_CHECK(argc,3);
    int ret;
    
    //输入客户名
    printf("please input your name:\n");
    char name[100]={0};
    read(STDIN_FILENO,name,sizeof(name));
    name[strlen(name)-1]=':';
    name[strlen(name)]=' ';

    //初始化缓冲区
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketfd,-1,"socket");
    
    //配置连接
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(atoi(argv[2]));
    ret=connect(socketfd,(struct sockaddr*)&server,sizeof(server));
    ERROR_CHECK(ret,-1,"connect");
    
    //多路转接实现即时聊天
    char buf[1000]={0};
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketfd,&rdset);
        ret=select(socketfd+1,&rdset,NULL,NULL,NULL);
        if(ret>0){
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                char sendstr[1100]={0};
                strcat(sendstr,name);
                strcat(sendstr,buf);
                send(socketfd,sendstr,strlen(sendstr)-1,0);
            }
            if(FD_ISSET(socketfd,&rdset)){
                bzero(buf,sizeof(buf));
                ret=recv(socketfd,buf,sizeof(buf),0);
                if(!ret){
                    printf("server has closed!\n");
                    break;
                }
                printf("%s\n",buf);
            }
        }
    }
    return 0;
}

