#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    FILE *fp = fdopen(fd, "r+");
    ERROR_CHECK(fp, NULL, "fdopen");
    char buf[128] = {0};
    fread(buf,1,sizeof(buf),fp);
    puts(buf);
    return 0;
}

