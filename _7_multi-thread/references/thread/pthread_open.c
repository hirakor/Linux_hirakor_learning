#include <func.h>
void * threadFunc(void *p)
{
    char buf[128]={0};
    int fd=(long)p;
    read(fd,buf,5);
    printf("I am child thread %s\n",buf);
    close(fd);
    return NULL;
}
int main(int argc,char *argv[])
{
    int ret;
    ARGS_CHECK(argc,2);
    pthread_t pthid;//线程ID
    long fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    ret=pthread_create(&pthid,NULL,threadFunc,(void*)fd);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    pthread_join(pthid,NULL);
    char buf[128]={0};
    ret=read(fd,buf,5);
    ERROR_CHECK(ret,-1,"read");
    printf("I am main thread,%s\n",buf);
    return 0;
}

