#include "client.h"

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
    recvCycle(socketFd,&dataLen,4);//拿火车头
    recvCycle(socketFd,buf,dataLen);//拿车厢
    int fd;
    int i=1;
    char tmp[1000];
    strcpy(tmp,buf);
    while((fd=open(tmp,O_RDWR|O_CREAT|O_EXCL,0666))==-1)
    {
        bzero(tmp,sizeof(tmp));
        sprintf(tmp,"%s%d",buf,i);
        i++;
    }
    //接收文件大小
    off_t fileSize;
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,&fileSize,dataLen);
    //接文件内容
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ftruncate(fd,fileSize);//做出对应大小的文件
    char *pStart=(char*)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pStart,(char*)-1,"mmap");
    ret=recvCycle(socketFd,pStart,fileSize);//拿数据
    if(0==ret)
    {
        munmap(pStart,fileSize);
        gettimeofday(&end,NULL);
        printf("100.00%s\n","%");
        printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    }else{
        printf("error load\n");
    }
    close(socketFd);
}
