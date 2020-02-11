#include "work_que.h"

int que_init(pQue_t pq,int Capacity)
{
    bzero(pq,sizeof(Que_t));
    pq->queCapacity=Capacity;
    pthread_mutex_init(&pq->queMutex,NULL);
    return 0;
}
//放入节点到队列里
int que_set(pQue_t pq,pNode_t pNew)
{
    if(!pq->queSize)//当队列为空
    {
        pq->queHead=pNew;
        pq->queTail=pNew;
    }else{
        pq->queTail->pNext=pNew;
        pq->queTail=pNew;
    }
    pq->queSize++;
    return 0;
}

int que_get(pQue_t pq,pNode_t *pTask)
{
    if(pq->queSize)
    {
        *pTask=pq->queHead;
        pq->queHead=pq->queHead->pNext;
        pq->queSize--;
        if(NULL==pq->queHead)
        {
            pq->queTail=NULL;
        }
    }
    return 0;
}
