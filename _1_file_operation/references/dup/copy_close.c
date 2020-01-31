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
    int fd1 = fd;
    close(fd);//将fd的值赋值给fd1以后，关闭fd
    printf("fd1 = %d\n", fd1);
    int ret = read(fd1, &ch, 1);
    ERROR_CHECK(ret, -1, "read");
    printf("read from fd1, ch = %c\n", ch);
    return 0;
}

