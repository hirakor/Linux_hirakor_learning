#include <func.h>

void cleanup(void *p)
{
    free(p);
    printf("free success\n");
}

void* threadfunc(void* p)
{
    p=malloc(20);
    pthread_cleanup_push(cleanup,p);
    printf("I am child thread\n");
    pthread_cleanup_pop(1);
    return NULL;
}

int main()
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadfunc,NULL);
    sleep(1);
    int ret=pthread_cancel(pthid);//cancel不能cancel已经结束的线程
    if(ret!=0)
    {
        printf("pthread_cancel failed ret=%d\n",ret);
    }
    long lret;
    pthread_join(pthid,(void**)&lret);
    printf("main thread %ld\n",lret);
    return 0;
}

