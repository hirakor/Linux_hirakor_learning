#include <func.h>
typedef struct{
    pthread_mutex_t mutex;
    long tickets;//票数
}thData;
void* threadfunc1(void *p)
{
    thData *p1=(thData*)p;
    while(1)
    {
        pthread_mutex_lock(&p1->mutex);
        if(p1->tickets>0)
        {
            printf("I am windows1,I will sale tickets %ld\n",p1->tickets);
            p1->tickets--;
            printf("I am windows1,sale ok %ld\n",p1->tickets);
            pthread_mutex_unlock(&p1->mutex);
        }else{
            pthread_mutex_unlock(&p1->mutex);
            break;
        }
        //sleep(1);
    }
}
void* threadfunc2(void *p)
{
    thData *p1=(thData*)p;
    while(1)
    {
        pthread_mutex_lock(&p1->mutex);
        if(p1->tickets>0)
        {
            printf("I am windows2,I will sale tickets %ld\n",p1->tickets);
            p1->tickets--;
            printf("I am windows2,sale ok %ld\n",p1->tickets);
            pthread_mutex_unlock(&p1->mutex);
        }else{
            pthread_mutex_unlock(&p1->mutex);
            break;
        }
        //sleep(1);
    }
}

int main()
{
    thData threadinfo;//结构体 
    int ret;
    ret=pthread_mutex_init(&threadinfo.mutex,NULL);
    if(ret!=0)
    {
        printf("pthread_mutex_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_t pthid1,pthid2;
    threadinfo.tickets=20;
    pthread_create(&pthid1,NULL,threadfunc1,&threadinfo);
    pthread_create(&pthid2,NULL,threadfunc2,&threadinfo);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    return 0;
}

