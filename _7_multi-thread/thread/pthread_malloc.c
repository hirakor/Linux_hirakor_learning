#include <func.h>

void* threadFunc(void *p){
    char *pStr=(char*)p;
    strcpy(pStr,"hello");
//    printf("I am child thread %s\n",pStr);
    return NULL;
}

int main(int argc,char* argv[]){
    int ret;
    pthread_t pthid;//线程id
    char *p=(char*)malloc(20);
    ret=pthread_create(&pthid,NULL,threadFunc,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
//    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    printf("main thread = %s\n",p);
    free(p);

    return 0;
}

