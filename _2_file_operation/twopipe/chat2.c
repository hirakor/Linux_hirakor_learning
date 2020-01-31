#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);   //是不是传了三个参数
    int fdw = open(argv[1],O_WRONLY);    //以写的方式打开第一条管道
    ERROR_CHECK(fdw,-1,"open");
    int fdr = open(argv[2],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open1");
    printf("I am wangyan\n");
    char buf[512]={0};
    int ret;
    while(1){
        ret = read(STDIN_FILENO,buf,sizeof(buf));
        ERROR_CHECK(ret,-1,"read");
        ret = write(fdw,buf,strlen(buf)-1);
        printf("%s\n",buf);
        ERROR_CHECK(ret,-1,"write");

        memset(buf,0,sizeof(buf));     //   清空buf
        ret = read(fdr,buf,sizeof(buf));
        printf("get %s\n",buf);
    }
    return 0;
}

