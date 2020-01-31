#include <func.h>
void cleanup(void *p){
    free(p);
    p=NULL;
    printf("have cleaned\n");
}
void *threadFunc(void* p){
    char *pStr=(char*)malloc(20);
    pthread_cleanup_push(cleanup,pStr);
    read(STDIN_FILENO,pStr,sizeof(pStr));
    printf("i am child thread %s\n",pStr);
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
}
int main(int argc,char* argv[])
{
    int ret;
    pthread_t pthid;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");   
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("i am mian thread, child exit code=%ld\n",threadRet);

    return 0;
}

