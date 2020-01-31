#include <func.h>
int global_k=0;
#define N 100000000
void * threadFunc(void *p)
{
    int i;
    for(i=0;i<N;i++)
    {
        global_k+=1;
    }
    return NULL;
}
int main()
{
    int ret,i;
    pthread_t pthid;//线程ID
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    //THREAD_ERROR_CHECK(ret,"pthread_create");
    for(i=0;i<N;i++)
    {
        global_k+=1;//不是原子操作
    }
    pthread_join(pthid,NULL);
    printf("I am main thread total=%d\n",global_k);
    return 0;
}

