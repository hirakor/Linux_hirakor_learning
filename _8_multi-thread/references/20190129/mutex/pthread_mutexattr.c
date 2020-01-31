#include <func.h>

int main()
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mattr;//线程锁属性
    int ret;
    ret=pthread_mutexattr_init(&mattr);
    pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_ERRORCHECK);
    ret=pthread_mutex_init(&mutex,&mattr);
    if(ret!=0)
    {
        printf("pthread_mutex_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_mutex_lock(&mutex);
    ret=pthread_mutex_lock(&mutex);
    printf("you can't see me,ret=%d\n",ret);
    pthread_mutex_destroy(&mutex);
    return 0;
}

