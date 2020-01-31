#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid=fork();
    if(0==pid){
        exit(0);
    }
    setsid();
    chdir("/");
    umask(0);
    for(int i=0;i<3;i++){
        close(i);
    }
    while(1){
        sleep(10);    //改成10秒看一看
        syslog(LOG_INFO,"wohenshuai\n");
    }
    return 0;
}
