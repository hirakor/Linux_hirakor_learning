#include <func.h>
void * threadFunc(void *p)
{
    char *pStr=(char*)malloc(20);
    strcpy(pStr,"hello");
    printf("I am child thread,%s\n",pStr);
    sleep(3);//被cancel,没有free，内存泄漏
    printf("I am child thread I am wake\n");
    pthread_exit(NULL);
}
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    //线程被cancel以后，接收到的返回值是-1
    printf("child exit code=%ld\n",threadRet);
    return 0;
}

