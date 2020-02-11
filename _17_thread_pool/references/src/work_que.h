#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"

typedef struct tag_node{
    int newFd;
    struct tag_node *pNext;
}Node_t,*pNode_t;

typedef struct{
    pNode_t queHead,queTail;
    int queCapacity;//队列能力
    int queSize;//队列当前的元素个数
    pthread_mutex_t queMutex;
}Que_t,*pQue_t;
int que_init(pQue_t,int);
int que_set(pQue_t,pNode_t);
int que_get(pQue_t,pNode_t*);
#endif
