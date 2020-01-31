#include <func.h>

int main(int argc,char* argv[])
{
    if(fork())
    {
        exit(0);
    }
    setsid();//成立新会话
    chdir("/");
    umask(0);
    for(int i=0;i<3;i++)
    {
        close(i);
    }
    while(1);
    return 0;
}

