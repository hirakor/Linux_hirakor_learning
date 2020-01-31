#include <func.h>
void * threadFunc(void *p)
{
    printf("I am child thread\n");
    p=(void*)1;
    pthread_exit(p);
}
int main()
{
    int ret;
    pthread_t pthid;//线程ID
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    long threadRetVal;
    ret=pthread_join(pthid,(void**)&threadRetVal);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread %ld\n",threadRetVal);
    return 0;
}

