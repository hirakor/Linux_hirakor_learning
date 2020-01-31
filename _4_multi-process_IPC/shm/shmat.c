#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;  //储存创建的共享内存   
    shmid = shmget(1000,4096,IPC_CREAT|0600);   //shmid储存shmget函数返回的唯一共享内存标识号
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget success %d\n",shmid);     //打印创建共享内存成功
    char *p=(char*)shmat(shmid,NULL,0);      //将共享内存段映射到指针p中储存的地址
    ERROR_CHECK(p,(char*)-1,"shmget");
  //  puts(p);
    strcpy(p,"I am shuai");                  //把字符复制到指针p对应的空间
    puts(p); 
    return 0;
}

