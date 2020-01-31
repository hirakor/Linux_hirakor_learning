#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    char ch;
    printf("fd = %d\n", fd);
    read(fd, &ch, 1);
    printf("read from fd, ch = %c\n", ch);
   //复制文件描述符以后，使用“赝品”去进行读 
    int fd2 = 100;
    dup2(fd, fd2);
    printf("fd2 = %d\n", fd2);
    read(fd2, &ch, 1);
    printf("read from fd1, ch = %c\n", ch);
    close(fd);
    return 0;
}

