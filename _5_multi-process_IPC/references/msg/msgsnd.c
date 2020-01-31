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
    buf.mtype=1;
    strcpy(buf.mtext,"hello");
    int ret=msgsnd(msgid,&buf,5,0);
    if(-1==ret)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}

