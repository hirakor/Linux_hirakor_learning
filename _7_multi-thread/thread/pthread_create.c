#include <func.h>

void* threadFunc(void *p){
    printf("I am child thread\n");
    return NULL;
}

int main(int argc,char* argv[]){
    int ret;
    pthread_t pthid;//线程id
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    usleep(500);

    return 0;
}

