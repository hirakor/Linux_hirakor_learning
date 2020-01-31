#include <func.h>

int main(int argc,char* argv[])
{
    int fds[2];
    pipe(fds);
    printf("fds[0]=%d,fds[1]=%d\n",fds[0],fds[1]);
    if(!fork())
    {
        close(fds[1]);//子进程要读，关闭写端
        int num=0;
        read(fds[0],&num,sizeof(int));
        printf("I am child get %d\n",num);
        exit(0);
    }else{
        close(fds[0]);//父进程要写，关闭读端
        int parent_num=10;
        write(fds[1],&parent_num,sizeof(int));
        wait(NULL);
        return 0;
    }
}

