#include <func.h>
//计数信号量
int main()
{
    int semArrid=semget(1000,2,IPC_CREAT|0600);
    if(-1==semArrid)
    {
        perror("semget");
        return -1;
    }
    unsigned short arr[2]={10,0};
    semctl(semArrid,0,SETALL,arr);
    struct sembuf sopp,sopv;
    if(!fork())
    {
        sopp.sem_num=1;
        sopp.sem_op=-1;
        sopp.sem_flg=SEM_UNDO;
        sopv.sem_num=0;
        sopv.sem_op=1;
        sopv.sem_flg=SEM_UNDO;
        while(1)
        {
             printf("I am customer,space=%d,product=%d\n",semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
             semop(semArrid,&sopp,1);
             printf("I have get one product\n");
             semop(semArrid,&sopv,1);
             printf("I am customer,space=%d,product=%d\n",semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
             sleep(2);
        }
    }else{
        sopp.sem_num=0;
        sopp.sem_op=-1;
        sopp.sem_flg=SEM_UNDO;
        sopv.sem_num=1;
        sopv.sem_op=1;
        sopv.sem_flg=SEM_UNDO;
        while(1)
        {
             printf("I am producer,space=%d,product=%d\n",semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
             semop(semArrid,&sopp,1);
             printf("I have produce one\n");
             semop(semArrid,&sopv,1);
             printf("I am producer,space=%d,product=%d\n",semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
             sleep(1);
        }
    }
    return 0;
}

