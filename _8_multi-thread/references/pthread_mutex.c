#include <func.h>

int main()
{
    pthread_mutex_t mutex;//定义一把锁
    int ret=pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    return 0;
}

