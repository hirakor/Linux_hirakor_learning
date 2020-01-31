#include <func.h>

int main(int argc,char *argv[]){
    pid_t pid=fork();
    if(0==pid){
        printf("I am child\n");
        return -1;
    }else{
        printf("I am parent\n");
        int status;
        pid=wait(&status);
        if(WIFEXITED(status)){
            printf("child exit code=%d\n",WEXITSTATUS(status));
        }else{
            printf("child crash\n");
        }
        printf("wait success,pid=%d\n",pid);
        return 0;
    }
    return 0;
}
