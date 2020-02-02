#include <func.h>

int main()
{
    pthread_cond_t cond;
    int ret;
    ret=pthread_cond_init(&cond,NULL);
    if(ret!=0)
    {
        printf("pthread_cond_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_cond_destroy(&cond);
    return 0;
}

