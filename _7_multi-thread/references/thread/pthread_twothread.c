#include <func.h>
void * threadFunc(void *p)
{
    int* pNum=(int*)p;
    printf("I am child thread %d\n",*pNum);
    return NULL;
}
//64位指针变量是8个字节
int main()
{
    int ret;
    pthread_t pthid,pthid1;//线程ID
    int i=1;
    ret=pthread_create(&pthid,NULL,threadFunc,&i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    i=2;
    ret=pthread_create(&pthid1,NULL,threadFunc,&i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    pthread_join(pthid1,NULL);
    printf("main thread over %d\n",i);
    return 0;
}

