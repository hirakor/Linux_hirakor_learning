#include <func.h>

int main()
{
    pthread_mutex_t mutex;
    int ret;
    ret=pthread_mutex_init(&mutex,NULL);
    if(ret!=0)
    {
        printf("pthread_mutex_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}

