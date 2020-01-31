#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;//存储创建的共享内存id
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    strcpy(p,"I am shuai");
    int ret;
    sleep(10);
    ret=shmdt(p);
    ERROR_CHECK(ret,-1,"shmdt");
    while(1);
    return 0;
}

