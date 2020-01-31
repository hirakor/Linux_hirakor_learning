#include <func.h>
#define N 50000000
int global_k=0;

void* threadFunc(void *p){
    int i;
    pthread_mutex_t *pmutex=(pthread_mutex_t *)p;
    for(i=0;i<N;i++){
        pthread_mutex_lock(pmutex);
        global_k+=1;
        pthread_mutex_unlock(pmutex);
    }
    //printf("I am child thread\n");
    return NULL;
}

int main(int argc,char* argv[]){
    int ret,i;
    pthread_t pthid;//线程id
    pthread_mutex_t mutex;
    ret=pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

    ret=pthread_create(&pthid,NULL,threadFunc,&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    for(i=0;i<N;i++){
        pthread_mutex_lock(&mutex);
        global_k+=1;  
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(pthid,NULL);
    printf("I am main thread    total=%d\n",global_k);
    return 0;
}

