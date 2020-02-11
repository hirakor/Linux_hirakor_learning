#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef struct{         //相当于整个工厂
    Que_t que;          //放的不是队列的指针，而是一个结构体
    pthread_cond_t cond;    //控制同步，先把所有的线程创建好，等待在这个条件变量上
    pthread_t *pthid;       //存储子线程id的起始地址，动态数组
    int threadNum;          //线程数目
    int startFlag;          //工厂是否启动
}Factory_t,*pFactory_t;

typedef struct{
    int dataLen;
    char buf[1000];
}train_t;

int factory_init(pFactory_t,int,int);
int factory_start(pFactory_t);
int tcp_init(int*,char*,char*);
int trans_file(int);

#endif

