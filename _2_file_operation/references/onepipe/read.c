#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);//是不是传递了一个参数
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    printf("I am reader\n");
    char buf[512]={0};
    int ret=read(fdr,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    printf("I get message %s\n",buf);
    return 0;
}

