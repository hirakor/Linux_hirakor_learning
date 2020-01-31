#include <func.h>
//用的是相对路径
int main(int argc,char* argv[])
{
    int ret=execl("./add","I am shuai","3","4",NULL);
    ERROR_CHECK(ret,-1,"execl");
    printf("you can't see me\n");
    return 0;
}

