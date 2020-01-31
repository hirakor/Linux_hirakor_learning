#include <func.h>

void* threadFunc(void *p){
    int *pNum=(int *)p;
    printf("I am child thread %d\n",*pNum);
    *pNum=5;
    return NULL;
}

int main(int argc,char* argv[]){
    int ret;
    pthread_t pthid;//线程id
    int i=10;
    ret=pthread_create(&pthid,NULL,threadFunc,&i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    printf("main thread=%d\n",i);

    return 0;
}

