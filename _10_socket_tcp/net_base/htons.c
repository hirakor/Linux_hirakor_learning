#include <func.h>
//  把小端变成大端，把主机字节序变成网络字节序
int main(int argc,char* argv[])
{
    unsigned short port=0x1234;
    printf("port=%x\n",port);
    unsigned short nport=htons(port);
    printf("nport=%x\n",nport);
    
    return 0;
}

