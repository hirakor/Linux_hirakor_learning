#include <func.h>
void * threadFunc(void *p)
{
    long pNum=(long)p;
    printf("I am child thread %ld\n",pNum);
    return NULL;
}
//64位指针变量是8个字节
int main()
{
    int ret;
    pthread_t pthid,pthid1;//线程ID
    long i=1;
    ret=pthread_create(&pthid,NULL,threadFunc,(void*)i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    i=2;
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&pthid1,NULL,threadFunc,(void*)i);
    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    pthread_join(pthid1,NULL);
    printf("main thread over %ld\n",i);
    return 0;
}

