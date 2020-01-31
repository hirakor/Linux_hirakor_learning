#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;  //储存创建的共享内存   
    shmid = shmget(1000,4096,IPC_CREAT|0600);   //shmid储存shmget函数返回的唯一共享内存标识号
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);     //打印创建共享内存成功
    //另一个进程连接共享内存，读取数据并打印
    if(fork()>0){
        char *p=(char*)shmat(shmid,NULL,0); //将共享内存段映射到指针p中储存的地址
        ERROR_CHECK(p,(char*)-1,"shmget");
        strcpy(p,"How are you");            //把字符复制到指针p对应的空间
        printf("parent=%d,write=%s\n",getpid(),p);
        sleep(3);
        wait(NULL);
        int ret=shmctl(shmid,IPC_RMID,NULL);    //删除共享内存
        ERROR_CHECK(ret,-1,"shmctl");
        //exit(0);
    }else{
       // sleep(2);
        char* q=(char*)shmat(shmid,NULL,0); //读内容
        printf("child=%d,shmid=%d,read=%s\n",getpid(),shmid,q);
        exit(0);

    }
    return 0;
}

