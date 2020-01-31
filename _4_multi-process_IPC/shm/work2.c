#include <func.h>
#define N 10000000

int main(int argc,char* argv[])
{
    int shmid;  //储存创建的共享内存   
    shmid = shmget(1000,4096,IPC_CREAT|0600);   //shmid储存shmget函数返回的唯一共享内存标识号
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);     //打印创建共享内存成功

    int *p=(int*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    p[0]=0;

    if(fork()>0){
        for(int i=0;i<N;i++){
            p[0]=p[0]+1;
        }
        exit(0);
    }else{
        for(int i=0;i<N;i++){
            p[0]=p[0]+1;
        }
        //sleep(5);
        wait(NULL);
        printf("result=%d\n",p[0]);
    }
    return 0;
}

