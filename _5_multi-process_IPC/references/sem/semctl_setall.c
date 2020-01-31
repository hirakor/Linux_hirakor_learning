#include <func.h>

int main()
{
    int semArrid=semget(1000,2,IPC_CREAT|0600);
    if(-1==semArrid)
    {
        perror("semget");
        return -1;
    }
    unsigned short arr[2]={3,4};
    semctl(semArrid,0,SETALL,arr);
    int ret;
    memset(arr,0,sizeof(arr));
    ret=semctl(semArrid,0,GETALL,arr);
    printf("%d %d\n",arr[0],arr[1]);
    return 0;
}

