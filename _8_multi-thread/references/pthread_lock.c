#include <func.h>
//主线程加锁，子线程解锁，是否可以
void * threadFunc(void *p)
{
    pthread_mutex_t *pmutex=(pthread_mutex_t*)p;
    pthread_mutex_unlock(pmutex);
    pthread_mutex_lock(pmutex);
    printf("I am child thread,exit\n");
    return NULL;
}
int main()
{
    int ret;
    pthread_t pthid;//线程ID
    pthread_mutex_t mutex;//定义一把锁
    ret=pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_create(&pthid,NULL,threadFunc,&mutex);
    pthread_mutex_lock(&mutex);
    pthread_join(pthid,NULL);
    printf("I am main thread \n");
    return 0;
}

