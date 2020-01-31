#include <func.h>
#define N 10000000
int main(int argc,char* argv[])
{
    int shmid;//存储创建的共享内存id
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget %d\n",shmid);
    int *p=(int*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    p[0]=0;
    int i;
    if(!fork())
    {
        for(i=0;i<N;i++)
        {
            p[0]=p[0]+1;
        }
        exit(0);
    }else{
        for(i=0;i<N;i++)
        {
            p[0]=p[0]+1;
        }
        wait(NULL);
        printf("result=%d\n",p[0]);
    }
}

