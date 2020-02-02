#include <func.h>
typedef struct{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}thData;
void* threadfunc(void *p)
{
    thData *p1=(thData*)p;
    pthread_mutex_lock(&p1->mutex);
    pthread_cond_wait(&p1->cond,&p1->mutex);
    pthread_mutex_unlock(&p1->mutex);
    printf("I am child\n");
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

