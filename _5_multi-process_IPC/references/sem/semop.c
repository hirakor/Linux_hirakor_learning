#include <func.h>

int main()
{
    int semArrid=semget(1000,1,IPC_CREAT|0600);
    if(-1==semArrid)
    {
        perror("semget");
        return -1;
    }
    int ret=semctl(semArrid,0,SETVAL,1);
    if(-1==ret)
    {
        perror("semctl");
        return -1;
    }
    struct sembuf sopp;
    sopp.sem_num=0;
    sopp.sem_op=-1;
    sopp.sem_flg=SEM_UNDO;
    semop(semArrid,&sopp,1);
    printf("you can't see me\n");
    return 0;
}

