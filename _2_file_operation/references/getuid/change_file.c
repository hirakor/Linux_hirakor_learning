#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    printf("uid=%d,euid=%d,gid=%d,egid=%d\n",getuid(),geteuid(),getgid(),getegid());
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    return 0;
}

