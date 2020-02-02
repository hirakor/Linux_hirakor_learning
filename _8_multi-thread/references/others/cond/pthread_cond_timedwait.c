#include <func.h>
typedef struct{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}thData;
void* threadfunc(void *p)
{
    thData *p1=(thData*)p;
    struct timespec t;
    memset(&t,0,sizeof(t));
    t.tv_sec=time(NULL)+3;//绝对时间
    pthread_mutex_lock(&p1->mutex);
    int ret=pthread_cond_timedwait(&p1->cond,&p1->mutex,&t);
    pthread_mutex_unlock(&p1->mutex);
    printf("I am child timedwait ret=%d\n",ret);
}
int main()
{
    int ret;
    thData threadinfo;
    ret=pthread_cond_init(&threadinfo.cond,NULL);
    if(ret!=0)
    {
        printf("pthread_cond_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_mutex_init(&threadinfo.mutex,NULL);
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadfunc,&threadinfo);
    sleep(1); 
    pthread_cond_signal(&threadinfo.cond);//发信号使得条件成立
    pthread_join(pthid,NULL); 
    return 0;
}

