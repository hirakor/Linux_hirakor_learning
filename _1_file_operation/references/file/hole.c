#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR|O_CREAT);
    ERROR_CHECK(fd,-1,"open");
    off_t ret = lseek(fd,1024,SEEK_SET);
    ERROR_CHECK(ret, (off_t)-1, "lseek");
    write(fd,"a",1);
    close(fd);
    return 0;
}

