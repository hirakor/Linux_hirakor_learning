#include <func.h>
typedef struct {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}thread_data_t;
void *threadFunc(void *p)
{
    thread_data_t *pdata=(thread_data_t*)p;
    printf("I am child thread\n");
    pthread_mutex_lock(&pdata->mutex);
    pthread_cond_wait(&pdata->cond,&pdata->mutex);
    pthread_mutex_unlock(&pdata->mutex);
    printf("wait over\n");
    pthread_exit(NULL);
}
int main()
{
    thread_data_t t;
    int ret,i;
    ret=pthread_cond_init(&t.cond,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_cond_init");
    pthread_mutex_init(&t.mutex,NULL);
    pthread_t pthid[2];
    for(i=0;i<2;i++){
        pthread_create(&pthid[i],NULL,threadFunc,&t);
    }
    sleep(1);//中间干了一些事
    ret=pthread_cond_broadcast(&t.cond);
    //ret=pthread_cond_signal(&t.cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_broadcast");
    //ret=pthread_cond_signal(&t.cond);
    for(i=0;i<2;i++){
        pthread_join(pthid[i],NULL);
    }
    printf("I am main thread,join success\n");
    return 0;
}

