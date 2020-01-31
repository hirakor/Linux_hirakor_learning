#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;//存储创建的共享内存id
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);
    int ret=shmctl(shmid,IPC_RMID,NULL);
    ERROR_CHECK(ret,-1,"shmctl");
    return 0;
}

