#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);   //是不是传了三个参数
    int fdr = open(argv[1],O_RDONLY);    //以读的方式打开第一条管道
    ERROR_CHECK(fdr,-1,"open");
    int fdw = open(argv[2],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open1");
    printf("I am peilei\n");
    char buf[512]={0};
    int ret;
    while(1){
        ret = read(fdr,buf,sizeof(buf));
        ERROR_CHECK(ret,-1,"read");
        printf("%s\n",buf);
        memset(buf,0,sizeof(buf));
        ret = read(STDIN_FILENO,buf,sizeof(buf));
        ret = write(fdw,buf,strlen(buf)-1);
    }
    return 0;
}

