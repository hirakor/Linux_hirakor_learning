#include <func.h>

int main()
{
    int semArrid=semget(1000,1,IPC_CREAT|0600);
    if(-1==semArrid)
    {
        perror("semget");
        return -1;
    }
    return 0;
}

