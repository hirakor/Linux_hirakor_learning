#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    struct hostent *p;
    p=gethostbyname(argv[1]);
    if(NULL==p){
        printf("gethostbyname failed\n");
        return -1;
    }
    printf("%s\n",p->h_name);
    int i;
    for(i=0;p->h_aliases[i]!=NULL;i++){
        printf("%s\n",p->h_aliases[i]);
    }
    printf("%d\n",p->h_addrtype);
    printf("%d\n",p->h_length);
    char ip[100]={0};
    for(i=0;p->h_aliases[i]!=NULL;i++){
        printf("%s\n",inet_ntop(p->h_addrtype,\
        p->h_addr_list[i],ip,sizeof(ip)));
    }
    return 0;
}

