#include <func.h>

int recvCycle(int newFd,void *pStart,int len)
{
    char *p=(char*)pStart;
    int total=0,ret;
    while(total<len)
    {
        ret=recv(newFd,p+total,len-total,0);
        if(0==ret)
        {
            printf("byebye\n");
            return -1;
        }
        total=total+ret;
    }
    return 0;
}

