#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");
    char buf[] = "HelloWorld";
    write(fdw, buf, strlen(buf));
    puts("over");
    close(fdw);
    return 0;
}

