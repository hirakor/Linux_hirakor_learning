#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");//这里会打印换行到屏幕
    int fd0 = 100;
    dup2(STDOUT_FILENO,fd0);
    //oldfd =1 newfd = 100 现在100指向屏幕
    int fd1 = dup2(fd,STDOUT_FILENO);
    //oldfd = fd newfd = 1 现在1指向文件
    printf("fd1 = %d\n", fd1);
    close(fd);
    printf("the out of stdout 1\n");
    //向文件输出内容
    dup2(fd0,STDOUT_FILENO);
    printf("the out of stdout 2\n");
    //向屏幕输出内容
    return 0;
}

