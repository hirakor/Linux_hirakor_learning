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
}

int main()
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadfunc,NULL);
    int ret=pthread_cancel(pthid);
    if(ret!=0)
    {
        printf("pthread_cancel failed ret=%d\n",ret);
    }
    long lret;
    pthread_join(pthid,(void**)&lret);
    printf("main thread %ld\n",lret);
    return 0;
}

