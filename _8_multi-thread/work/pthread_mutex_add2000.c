#include <func.h>
#define N 20000000
typedef struct{
    pthread_mutex_t mutex;
    long num;
}the_Data;
void *threadFunc(void* p){
    the_Data *p1=(the_Data*)p;
    int i;
    for(i=0;i<N;i++){
        pthread_mutex_lock(&p1->mutex);
        p1->num+=1;
        pthread_mutex_unlock(&p1->mutex);
    }
    return NULL;
}
int main(int argc,char* argv[])
{
    the_Data threadinfo;
    int ret;
    ret=pthread_mutex_init(&threadinfo.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    if(ret!=0){
        printf("pthread_mutex_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_t pthid;
    threadinfo.num=0;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ret=pthread_create(&pthid,NULL,threadFunc,&threadinfo);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    int i;
    for(i=0;i<N;i++){
        pthread_mutex_lock(&threadinfo.mutex);
        threadinfo.num+=1;
        pthread_mutex_unlock(&threadinfo.mutex);
    }
    ret=pthread_join(pthid,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    gettimeofday(&end,NULL);
    printf("result=%ld,usetime=%ld\n",threadinfo.num,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    return 0;
}

