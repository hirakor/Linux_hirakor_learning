#include <func.h>

void* threadFunc(void *p){
    char buf[128]={0};
    int fd=(long)p;
    read(fd,buf,5);
    printf("I am child thread %s\n",buf);
    close(fd);
    return NULL;
}

int main(int argc,char* argv[]){
    int ret;
    ARGS_CHECK(argc,2);
    pthread_t pthid;//线程id
    long fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    ret=pthread_create(&pthid,NULL,threadFunc,(void*)fd);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    char buf[128]={0};
    ret=read(fd,buf,5);
    ERROR_CHECK(fd,-1,"read");
    printf("I am main thread\n");

    return 0;
}

