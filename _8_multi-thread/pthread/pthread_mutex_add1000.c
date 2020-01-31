#include <func.h>
#define N 10000000
typedef struct{
    pthread_mutex_t mutex;
    long iNum;
}thData;

void* threadFunc(void *p){
    thData *p1=(thData*)p;
    int i;
    for(i=0;i<N;i++){
        pthread_mutex_lock(&p1->mutex);
        p1->iNum=p1->iNum+1;
        pthread_mutex_unlock(&p1->mutex);
    }
    return NULL;
}

int main(int argc,char* argv[]){
    thData threadinfo;
    int ret;
    ret=pthread_mutex_init(&threadinfo.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    if(ret!=0){
        printf("pthread_mutex_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_t pthid;
    threadinfo.iNum=0;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ret=pthread_create(&pthid,NULL,threadFunc,&threadinfo);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    int i;
    for(i=0;i<N;i++){
        pthread_mutex_lock(&threadinfo.mutex);
        threadinfo.iNum+=1;  
        pthread_mutex_unlock(&threadinfo.mutex);
    }
    pthread_join(pthid,NULL);
    gettimeofday(&end,NULL);
    printf("result=%ld,usetime=%ld\n",threadinfo.iNum,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    return 0;
}

