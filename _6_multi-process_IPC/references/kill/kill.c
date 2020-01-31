#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    pid_t pid;
    pid=atoi(argv[1]);
    kill(pid,SIGINT);
    return 0;
}

