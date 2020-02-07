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
    int dataLen;
    char buf[1000]={0};
    //先接文件名
    recv(socketFd,&dataLen,4,0);    //拿火车头
    recv(socketFd,buf,dataLen,0);   //拿火车车厢
    int fd;
    int i=1;
    char tmp[1000];
    strcpy(tmp,buf);
    while((fd=open(tmp,O_WRONLY|O_CREAT|O_EXCL,0666))==-1){
        bzero(tmp,sizeof(tmp));
        sprintf(tmp,"%s%d",buf,i);
        i++;
    }
    //接文件内容
    while(1){
        recv(socketFd,&dataLen,4,0);   //拿火车头
        if(dataLen>0){
            recv(socketFd,buf,dataLen,0);   //拿火车内容
            write(fd,buf,dataLen);  //把接到的数据写到磁盘上
        }else{
            break;
        }
    }
    close(socketFd);
}
