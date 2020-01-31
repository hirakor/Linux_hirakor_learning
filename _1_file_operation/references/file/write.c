#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char buf[128] = "howareyou";
    int ret = write(fd,buf,strlen(buf));
    ERROR_CHECK(ret, -1, "write");
    printf("buf = %s, ret = %d\n", buf, ret);
    close(fd);
    return 0;
}

