#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    if(!fork()){
        printf("I am child %s\n",p);
        exit(0);
    }else{
        strcpy(p,"I am your parent");
        wait(NULL);
        printf("programme over\n");
    }
    return 0;
}

