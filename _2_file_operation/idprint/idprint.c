#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    pid_t pid,ppid;
    pid = getpid();
    ppid = getppid();
    printf("mypid=%d,ppid=%d,uid=%d,gid=%d,euid=%d,egid=%d\n"\
           ,pid,ppid,getuid(),getgid(),geteuid(),getegid());
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    return 0;
}

