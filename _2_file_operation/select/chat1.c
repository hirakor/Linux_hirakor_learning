#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);   //是不是传了三个参数
    int fdr = open(argv[1],O_RDONLY);    //以读的方式打开第一条管道
    ERROR_CHECK(fdr,-1,"open");
    int fdw = open(argv[2],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open1");
    printf("I am peilei\n");
    char buf[512]={0};
    int ret;
    fd_set rdset;        //定义一个集合
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(0,&rdset);
        FD_SET(fdr,&rdset);
        ret = select(fdr+1,&rdset,NULL,NULL,NULL);  //rdset是传入传出参数
        if(FD_ISSET(0,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret = read(STDIN_FILENO,buf,sizeof(buf));
            if(0==ret)
            {
                printf("I want to break up\n");
                break;
            }
            ret = write(fdw,buf,strlen(buf)-1);
        }
        if(FD_ISSET(fdr,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret = read(fdr,buf,sizeof(buf));
            ERROR_CHECK(ret,-1,"read");
            if(0==ret)
            {
                printf("byebye\n");
                break;
            }
            printf("%s\n",buf); 
        }
    }
    return 0;
}
