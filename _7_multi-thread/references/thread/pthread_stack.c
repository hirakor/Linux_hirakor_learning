#include <func.h>
void * threadFunc(void *p)
{
    int* pNum=(int*)p;
    printf("I am child thread %d\n",*pNum);
    *pNum=5;
    return NULL;
}
//64位指针变量是8个字节
int main()
{
    int ret;
    pthread_t pthid;//线程ID
    int i=10;
    ret=pthread_create(&pthid,NULL,threadFunc,&i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    printf("main thread=%d\n",i);
    return 0;
}

