#include <stdio.h>
#include <sys/time.h>
int main()
{
    struct timeval start,end;
    int i,ret=0;
    gettimeofday(&start,NULL);
    for(i=0;i<20000000;i++)
    {
        ret=ret+1;
    }
    gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    return 0;
}

