#include <func.h>

void* threadFunc(void *p){
    printf("I am child thread\n");
    p=malloc(20);
    strcpy((char*)p,"hello");
    pthread_exit(p);
}

int main(int argc,char* argv[]){
    int ret;
    pthread_t pthid;//线程id
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    void *pRet;
    ret=pthread_join(pthid,&pRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread %s\n",(char*)pRet);
    free(pRet);

    return 0;
}

