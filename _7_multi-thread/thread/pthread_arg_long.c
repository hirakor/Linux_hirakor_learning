#include <func.h>

void* threadFunc(void *p){
    long pNum=(long)p;//将int* 类型改为 long 类型
    printf("I am child thread %ld\n",pNum);//将解引用 pNum 改为 pNum
    return NULL;
}
//64位指针变量是8个字节
int main(int argc,char* argv[]){
    int ret;
    pthread_t pthid,pthid1;//线程id
    long i=1;//将 int 类型改为 long 类型
    ret=pthread_create(&pthid,NULL,threadFunc,(void*)i);//将取地址i改为强制类型转换i
    THREAD_ERROR_CHECK(ret,"pthread_create");
    
    i=2;
    ret=pthread_create(&pthid1,NULL,threadFunc,(void*)i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");

    pthread_join(pthid,NULL);
    pthread_join(pthid1,NULL);
    printf("main thread over %ld\n",i);

    return 0;
}

