#include <func.h>

void cleanup(void *p)
{
   printf("I am cleanup func %ld\n",(long)p);
}

void* threadfunc(void* p)
{
    pthread_cleanup_push(cleanup,(void*)1);
    pthread_cleanup_push(cleanup,(void*)2);
    printf("I am child thread\n");
    sleep(2);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}

int main()
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadfunc,NULL);
    sleep(1); 
    pthread_cancel(pthid);
    long lret;
    pthread_join(pthid,(void**)&lret);
    printf("main thread %ld\n",lret);
    return 0;
}

