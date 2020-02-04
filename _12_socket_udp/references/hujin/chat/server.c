#include <func.h>
typedef struct node{
    int tag;
    struct sockaddr_in addr;
}info_t;
int main(int argc,char **argv){
    ARGS_CHECK(argc,3);
    int ret;

    //初始化缓冲区
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketfd,-1,"socket");

    //配置套接口
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(atoi(argv[2]));
    ret=bind(socketfd,(struct sockaddr*)&server,sizeof(server));
    ERROR_CHECK(ret,-1,"bind");

    //激活端口
    listen(socketfd,100);//最多100人同时在线

    //设置描述符集合，一个用于单次连接，一个用于汇总记录
    fd_set mainset,rdset;
    FD_ZERO(&mainset);
    FD_SET(socketfd,&mainset);

    //多路转接实现即时聊天
    char buf[1000]={0};
    char message[100]={0};
    int newfd;//用于保存新建连接的描述符
    struct sockaddr_in client;
    info_t infoarr[104];//用于标记在线的描述符
    bzero(&infoarr,sizeof(infoarr));
    int retfd;
    int i,j;
    while(1){
        FD_ZERO(&rdset);
        memcpy(&rdset,&mainset,sizeof(fd_set));
        retfd=select(104,&rdset,NULL,NULL,NULL);
        if(retfd>0){
            if(FD_ISSET(socketfd,&rdset)){
                //新建连接并接收对方socket信息
                bzero(&client,sizeof(client));
                socklen_t len=sizeof(client);
                newfd=accept(socketfd,(struct sockaddr*)&client,&len);
                ERROR_CHECK(newfd,-1,"accept");
                bzero(buf,sizeof(buf));
                recv(newfd,buf,sizeof(buf),0);
                infoarr[newfd].tag=1;
                infoarr[newfd].addr=client;
                for(i=4;i<104;i++){
                    //向在线用户打印新登录信息
                    if(infoarr[i].tag){
                        bzero(message,sizeof(message));
                        sprintf(message,"%s:port %d online\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                        send(i,message,strlen(message),0);
                        send(i,buf,strlen(buf),0);
                    }
                }
                FD_SET(newfd,&mainset);
            }
            else{
                for(i=4;i<104;i++){
                    if(FD_ISSET(i,&rdset)){
                        bzero(buf,sizeof(buf));
                        ret=recv(i,buf,sizeof(buf),0);
                        if(!ret){
                            FD_CLR(i,&mainset);
                            infoarr[newfd].tag=0;
                            for(j=4;j<104;j++){
                                //向在线用户打印离线信息
                                if(infoarr[j].tag){
                                    bzero(message,sizeof(message));
                                    sprintf(message,"%s:port %d offline",inet_ntoa(infoarr[i].addr.sin_addr),ntohs(infoarr[i].addr.sin_port));
                                    send(j,message,strlen(message),0);
                                }
                            }
                            close(i);
                            continue;
                        }
                        for(int i=3;i<104;i++){
                            //向在线用户打印对话
                            if(infoarr[i].tag){
                                send(i,buf,strlen(buf),0);
                            }
                        }
                    }
                }
            }
        }
    }
    close(socketfd);
    return 0;
}
