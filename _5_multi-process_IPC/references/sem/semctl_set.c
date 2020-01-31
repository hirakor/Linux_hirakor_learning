#include <func.h>

int main()
{
    int semArrid=semget(1000,1,IPC_CREAT|0600);
    if(-1==semArrid)
    {
        perror("semget");
        return -1;
    }
    struct semid_ds buf;
    semctl(semArrid,0,IPC_STAT,&buf);
    printf("%o %ld\n",buf.sem_perm.mode,buf.sem_nsems);
    buf.sem_perm.mode=0666;
    semctl(semArrid,0,IPC_SET,&buf);
    return 0;
}

