#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    struct in_addr addr;
    inet_aton(argv[1],&addr);
    printf("net addr = %x\n",addr.s_addr);
    printf("ip=%s\n",inet_ntoa(addr));
    printf("net addr=%x\n",inet_addr(argv[1]));

    return 0;
}

