#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    FILE* fp = fopen(argv[1],"r+");
    //使用fopen打开一个文件缓冲区
    char buf[128] = {0};
    int ret = read(3, buf, sizeof(buf));
    //使用read利用文件描述符进行读取
    ERROR_CHECK(ret, -1, "read");
    puts(buf);
    return 0;
}

