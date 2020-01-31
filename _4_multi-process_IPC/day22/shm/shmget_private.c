#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;//存储创建的共享内存id
    shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);
    return 0;
}

