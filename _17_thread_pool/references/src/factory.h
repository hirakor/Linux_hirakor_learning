#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef struct{
    Que_t que;
    pthread_cond_t cond;//控制同步
    pthread_t *pthid;//存储子线程ID的起始地址
    int threadNum;//线程数目
    int startFlag;//工厂是否启动
}Factory_t,*pFactory_t;
typedef struct{
    int dataLen;//存储的是 buf上到底运了多少数据
    char buf[1000];//存储要发送的数据
}train_t;
int factory_init(pFactory_t,int,int);
int factory_start(pFactory_t);
int tcp_init(int*,char*,char*);
int trans_file(int);
#endif
