#include <func.h>
struct msgbuf{
    long mtype;
    char mtext[64];
};

int main()
{
    int msgid;
    msgid=msgget(1000,IPC_CREAT|0600);
    if(-1==msgid)
    {
        perror("msgget");
        return -1;
    }
    struct msgbuf buf;
    memset(&buf,0,sizeof(buf));
    int ret=msgrcv(msgid,&buf,sizeof(buf.mtext),0,0);
    if(-1==ret)
    {
        perror("msgrcv");
        return -1;
    }
    printf("%ld %s\n",buf.mtype,buf.mtext);
    return 0;
}

