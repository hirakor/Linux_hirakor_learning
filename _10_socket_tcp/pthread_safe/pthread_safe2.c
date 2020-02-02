#include <func.h>
void *threadFunc(void *p){   
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
int main(){
    int ret;
    pthread_t pthid;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pexthread_create");
    sleep(2);
    time_t t;
    time(&t);
    char *ptime=ctime(&t);
    printf("main ptime=%p,ptime=%p\n",ptime,&ptime);
    printf("I am main thread %s\n",ptime);
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,join success, child exit code=%ld\n",threadRet);
    return 0;
}

