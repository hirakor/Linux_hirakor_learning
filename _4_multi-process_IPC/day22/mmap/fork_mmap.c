#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char *p;
    p=(char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap");
    if(!fork())
    {
        printf("I am child %s\n",p);
        return 0;
    }else{
        p[0]='H';
        wait(NULL);
        return 0;
    }
}

