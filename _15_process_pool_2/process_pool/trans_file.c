#include "process_pool.h"
#define FILENAME "file"

int trans_file(int newFd){
    //发送文件名
    train_t dataTrain;
    dataTrain.dataLen=strlen(FILENAME); //规范的来说是要转换大小端
    strcpy(dataTrain.buf,FILENAME);
    send(newFd,&dataTrain,4+dataTrain.dataLen,0);
    //发送文件内容
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    while((dataTrain.dataLen=read(fd,dataTrain.buf,sizeof(dataTrain.buf)))){
        send(newFd,&dataTrain,4+dataTrain.dataLen,0);
    }
    //发结束标志
    dataTrain.dataLen=0;
    send(newFd,&dataTrain,4,0);

    return 0;
}

