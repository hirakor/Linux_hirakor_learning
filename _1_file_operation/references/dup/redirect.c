#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    dup2(fd,1);
    printf("howoldareyou\n");
    //printf的原理：向文件描述符为1的文件进行写入
    close(fd);
    return 0;
}

