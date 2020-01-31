#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char ch;
    read(fd,&ch,sizeof(char));
    printf("ch = %c\n", ch);
    off_t ret = lseek(fd,1,SEEK_CUR);
    ERROR_CHECK(ret,(off_t)-1, "lseek");
    read(fd,&ch,sizeof(char));
    printf("ch = %c\n", ch);
    close(fd);
    return 0;
}

