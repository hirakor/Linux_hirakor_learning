#include <func.h>

int main(int argc,char* argv[])
{
    int sems_id=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(sems_id,-1,"semget");
    int ret=semctl(sems_id,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl");
    ret=semctl(sems_id,0,GETVAL);
    printf("value = %d\n",ret);

    return 0;
}

