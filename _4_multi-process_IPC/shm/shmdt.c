#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    strcpy(p,"I am shuai");
    sleep(3);
    int ret=shmdt(p);       //共享空间和内存空间段分离
    ERROR_CHECK(p,(char*)-1,"shmat");
    //while(1);
    return 0;
}

