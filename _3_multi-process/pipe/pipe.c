#include <func.h>

int main(int argc,char *argv[])
{
    int fds[2];
    pipe(fds);
    printf("fds[0]=%d,fds[1]=%d\n",fds[0],fds[1]);
    if(!fork()){
        close(fds[0]);
        write(fds[1],"Hello",5);
        exit(0);
    }else{
        close(fds[1]);
        char buf[128]={0};
        read(fds[0],buf,sizeof(buf));
        wait(NULL);
        puts(buf);
        return 0;
    }
}

