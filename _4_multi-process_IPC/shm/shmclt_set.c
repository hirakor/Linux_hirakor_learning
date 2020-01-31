#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);
    struct shmid_ds buf;
    int ret=shmctl(shmid,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("cuid=%d,mode=%o,size=%ld,nattch=%ld\n",\
            buf.shm_perm.cuid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    buf.shm_perm.mode=0666;
    ret= shmctl(shmid,IPC_SET,&buf);
    ERROR_CHECK(ret,-1,"shmctl");

    return 0;
}

