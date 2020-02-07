#include<func.h>

typedef struct{
    pid_t pid;  //子进程的 pid
    int fd;     //子进程的管道对端
    short busy; //子进程的状态
}process_data_t;

typedef struct{
    int dataLen;    //储存的是 buf 上面到底存了多少数据
    char buf[1000]; //储存要发送的数据
}train_t;

int make_child(process_data_t*,int);
int child_handle(int);
int tcp_init(int*,char*,char*);     //初始化socket、bind、listen
int sendFd(int,int);
int recvFd(int,int*);
int trans_file(int);
