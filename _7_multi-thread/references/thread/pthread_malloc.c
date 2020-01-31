#include <func.h>
void * threadFunc(void *p)
{
    //子线程往里边放数据
    char *pStr=(char*)p;
    strcpy(pStr,"hello");
    printf("I am child thread %s\n",pStr);
    return NULL;
}
//64位指针变量是8个字节
int main()
{
    int ret;
    pthread_t pthid;//线程ID
    char *p=(char*)malloc(20);
    ret=pthread_create(&pthid,NULL,threadFunc,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    printf("main thread=%s\n",p);
    return 0;
}

