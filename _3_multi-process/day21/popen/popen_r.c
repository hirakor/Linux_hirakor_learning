#include <func.h>

int main(int argc,char* argv[])
{
    FILE *fp;
    fp=popen("./print","r");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[1024]={0};
    fread(buf,sizeof(char),sizeof(buf),fp);
    printf("popen:%s",buf);
    pclose(fp);
    return 0;
}

