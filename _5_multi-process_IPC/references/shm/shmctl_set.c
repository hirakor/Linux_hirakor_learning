#include <func.h>

int main()
{
    int shmid=shmget(1000,4096,IPC_CREAT|0600);
    if(-1==shmid)
    {
        perror("shmget");
        return -1;
    }
    struct shmid_ds buf;
    int ret=shmctl(shmid,IPC_STAT,&buf);
    if(-1==ret)
    {
        perror("shmctl");
        return -1;
    }
    printf("%d %o %ld %ld\n",buf.shm_perm.cuid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    buf.shm_perm.mode=0666;
    ret=shmctl(shmid,IPC_SET,&buf);
    if(-1==ret)
    {
        perror("shmctl1");
        return -1;
    }
    return 0;
}
