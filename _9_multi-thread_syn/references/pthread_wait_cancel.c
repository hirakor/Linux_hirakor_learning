#include <func.h>
typedef struct {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}thread_data_t;
void cleanup(void *p)
{
    pthread_mutex_unlock((pthread_mutex_t*)p);
}
void *threadFunc(void *p)
{
    thread_data_t *pdata=(thread_data_t*)p;
    printf("I am child thread\n");
    pthread_mutex_lock(&pdata->mutex);
    pthread_cleanup_push(cleanup,&pdata->mutex);
    pthread_cond_wait(&pdata->cond,&pdata->mutex);
    pthread_cleanup_pop(1);
    printf("wait over\n");
    pthread_exit(NULL);
}
//wait被cancel后如何避免死锁的问题
int main()
{
    thread_data_t t;
    int ret;
    ret=pthread_cond_init(&t.cond,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_cond_init");
    pthread_mutex_init(&t.mutex,NULL);
    pthread_t pthid[2];
    int i;
    for(i=0;i<2;i++)
    {
        pthread_create(pthid+i,NULL,threadFunc,&t);
    }
    sleep(1);//中间干了一些事
    for(i=0;i<2;i++)
    {
        ret=pthread_cancel(pthid[i]);
        THREAD_ERROR_CHECK(ret,"pthread_cancel");
    }
//    ret=pthread_cond_signal(&t.cond);
//    THREAD_ERROR_CHECK(ret,"pthread_cond_signal");
//    ret=pthread_cond_signal(&t.cond);
    long threadRet;
    for(i=0;i<2;i++)
    {
        pthread_join(pthid[i],(void**)&threadRet);
        printf("join success %ld\n",threadRet);
    }
    printf("I am main thread,join success\n");
    return 0;
}

