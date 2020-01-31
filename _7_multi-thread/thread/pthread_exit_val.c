#include <func.h>

void* threadFunc(void *p){
    long pNum=(long)p;
    printf("I am child thread,get %ld\n",pNum);
    p=(void*)2;
    pthread_exit(p);
}

int main(int argc,char* argv[]){
    int ret;
    pthread_t pthid;//线程id
    long i=1;
    ret=pthread_create(&pthid,NULL,threadFunc,(void*)i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    long RetVal;
    ret=pthread_join(pthid,(void**)&RetVal);//把返回值放进RetVal里面
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,get %ld\n",RetVal);

    return 0;
}

