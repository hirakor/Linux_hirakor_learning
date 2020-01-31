#include <func.h>

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,3);
    puts(argv[0]);
    int first = atoi(argv[1]);
    int second = atoi(argv[2]);
    printf("sum = %d\n",first+second);

    return 0;
}

