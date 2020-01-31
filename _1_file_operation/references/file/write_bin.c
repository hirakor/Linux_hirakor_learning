#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret = write(fd,&fd,sizeof(fd));
    ERROR_CHECK(ret, -1, "write");
    printf("ret = %d\n",ret);
    close(fd);
    return 0;
}

