#include <func.h>
void cleanup(void *p){
    free(p);
    p=NULL;
    printf("I am cleanup\n");
}

void * threadFunc(void *p){
    char *pStr=(char*)malloc(20);
    pthread_cleanup_push(cleanup,pStr);
    strcpy(pStr,"jisoo");
    printf("I am child thread\n");
    sleep(3);
    printf("I am child thread I am wake\n");
    pthread_exit(NULL);
    pthread_cleanup_pop(1);
}

int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
//    ret=pthread_cancel(pthid);
//    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    //线程被cancel以后，接收到的返回值是-1
    printf("child exit code = %ld\n",threadRet);
    
    return 0;
}

