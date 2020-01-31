#include <func.h>
#define N 50000000
int global_k=0;
void* threadFunc(void *p){
    int i;
    for(i=0;i<N;i++){
        global_k+=1;
    }
    printf("I am child thread\n");
    return NULL;
}

int main(int argc,char* argv[]){
    int ret,i;
    pthread_t pthid;//线程id
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    for(i=0;i<N;i++){
        global_k+=1;  
    }
    pthread_join(pthid,NULL);
    printf("I am main thread    total=%d\n",global_k);
//    usleep(500);
    return 0;
}

