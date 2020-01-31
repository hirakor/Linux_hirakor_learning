#include <func.h>

int main(int argc,char* argv[])
{
    printf("uid=%d,euid=%d,gid=%d,egid=%d\n",getuid(),geteuid(),getgid(),getegid());
    return 0;
}

