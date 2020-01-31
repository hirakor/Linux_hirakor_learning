#include <func.h>

int main()
{
    int shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    if(-1==shmid)
    {
        perror("shmget");
        return -1;
    }
   // int ret=shmctl(shmid,IPC_RMID,NULL);
   // if(-1==ret)
   // {
   //     perror("shmctl");
   //     return -1;
   // }
    return 0;
}
