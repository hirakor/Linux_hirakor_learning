#include <func.h>

int main(int argc,char* argv[])
{
    FILE *fp;
    fp=popen("./scanf","w");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[128]="4 5";
    fwrite(buf,sizeof(char),strlen(buf),fp);
    pclose(fp);
    return 0;
}

