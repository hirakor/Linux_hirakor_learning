#include <func.h>
#define N 10000000
void* threadfunc(void *p)
{
    printf("I am child\n");
}
int main()
{
    int ret;
    pthread_t pthid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_create(&pthid,&attr,threadfunc,NULL);
    ret=pthread_join(pthid,NULL);
    printf("pthread_join ret=%d\n",ret);
    return 0;
}

