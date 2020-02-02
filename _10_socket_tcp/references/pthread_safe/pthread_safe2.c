#include <func.h>
void * threadFunc(void *p)
{
    //ctime不是线程安全的接口
    time_t t;
    time(&t);
    char buf[128]={0};
    char *ptime=ctime_r(&t,buf);
    printf("child ptime=%p,ptime=%p\n",ptime,&ptime);
    printf("I am child thread %s\n",ptime);
    sleep(3);
    printf("I am child thread %s\n",ptime);
    pthread_exit(NULL);
}
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    sleep(2);
    time_t t;
    time(&t);
    char *ptime=ctime(&t);
    printf("main ptime=%p,ptime=%p\n",ptime,&ptime);
    printf("I am main thread %s\n",ptime);
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("child exit code=%ld\n",threadRet);
    return 0;
}

