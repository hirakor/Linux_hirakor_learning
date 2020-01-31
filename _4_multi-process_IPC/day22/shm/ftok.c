#include <func.h>

int main(int argc,char* argv[])
{
    key_t key;
    ARGS_CHECK(argc,2);
    key=ftok(argv[1],1);
    printf("key=%d\n",key);
    return 0;
}

