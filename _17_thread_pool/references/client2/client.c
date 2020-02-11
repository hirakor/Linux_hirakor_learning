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
    while((fd=open(tmp,O_WRONLY|O_CREAT|O_EXCL,0666))==-1)
    {
        bzero(tmp,sizeof(tmp));
        sprintf(tmp,"%s%d",buf,i);
        i++;
    }
    //接收文件大小
    off_t fileSize,downLoadSize=0,fileSlice,lastLoadSize=0;
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,&fileSize,dataLen);
    fileSlice=fileSize/10000;
    //接文件内容
    struct timeval start,end;
    gettimeofday(&start,NULL);
    while(1)
    {
        ret=recvCycle(socketFd,&dataLen,4);//拿火车头
        if(0==ret&&dataLen>0)
        {
            ret=recvCycle(socketFd,buf,dataLen);//拿车厢
            if(-1==ret)
            {
                break;
            }
            write(fd,buf,dataLen);//把接到的数据写到磁盘上
            downLoadSize+=dataLen;
            if(downLoadSize-lastLoadSize>=fileSlice)
            {
                printf("%5.2f%s\r",(double)downLoadSize/fileSize*100,"%");
                fflush(stdout);
                lastLoadSize=downLoadSize;
            }
        }else{
            gettimeofday(&end,NULL);
            printf("100.00%s\n","%");
            printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
            break;
        }
    }
    close(socketFd);
}
