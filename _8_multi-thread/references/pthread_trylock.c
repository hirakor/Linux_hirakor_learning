#include <func.h>
//同一个线程对一把锁加锁两次，死锁
int main()
{
    pthread_mutex_t mutex;//定义一把锁
    int ret=pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    pthread_mutex_lock(&mutex);
    ret=pthread_mutex_trylock(&mutex);
    printf("ret=%d\n",ret);
    return 0;
}

