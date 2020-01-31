#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret = ftruncate(fd, 5);
    ERROR_CHECK(ret, -1, "ftruncate");
    char *p;
    p = (char *)mmap(NULL,
                     5,
                     PROT_READ|PROT_WRITE,
                     MAP_SHARED,
                     fd,
                     0);//建立内存和磁盘文件之间的映射
    ERROR_CHECK(p, (void *)-1, "mmap");
    p[5] = 0;//不会影响到文件，方便puts
    puts(p);//读取文件内容
    p[0] = 'H';//写入文件
    munmap(p,5);
    close(fd);
    return 0;
}

