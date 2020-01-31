#include <func.h>
int global_k=10;
void * threadFunc(void *p)
{
    printf("I am child thread global_k=%d\n",global_k);
    return NULL;
}
int main()
{
    int ret;
    pthread_t pthid;//线程ID
    printf("I am main thread global_k=%d\n",global_k);
    global_k=5; 
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    usleep(1000);
    return 0;
}

