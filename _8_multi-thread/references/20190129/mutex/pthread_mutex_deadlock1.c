#include <func.h>
#define N 10000000
typedef struct{
    pthread_mutex_t mutex;
    long iNum;
}thData;
void* threadfunc(void *p)
{
    thData *p1=(thData*)p;
    pthread_mutex_lock(&p1->mutex);
    printf("I am child\n");
}

int main()
{
    thData threadinfo; 
    int ret;
    ret=pthread_mutex_init(&threadinfo.mutex,NULL);
    if(ret!=0)
    {
        printf("pthread_mutex_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_t pthid;
    threadinfo.iNum=0;
    pthread_create(&pthid,NULL,threadfunc,&threadinfo);
    int i;
    sleep(1);
    pthread_mutex_lock(&threadinfo.mutex);
    printf("main thread lock success\n");
    pthread_join(pthid,NULL);
    printf("I am main thread\n");
    return 0;
}

