#include <func.h>
//用的是相对路径
int main(int argc,char* argv[])
{
    char * const envp[]={"PATH=/usr/bin",NULL};
    int ret=execle("./test_path","test_path",NULL,envp);
    ERROR_CHECK(ret,-1,"execl");
    printf("you can't see me\n");
    return 0;
}

