#include <func.h>
int main(int argc, char** argv)
{
	ARGS_CHECK(argc,2);
	DIR *pdir = opendir(argv[1]);
	ERROR_CHECK(pdir,NULL,"opendir");
	struct dirent *pbuf;
    off_t pos = telldir(pdir);//获取目录项的位置
	while( (pbuf = readdir(pdir)) != NULL)
	{
		printf("%s %d\n",pbuf->d_name, pbuf->d_type);
	}
    puts("这是一个分隔符------------------------");
    seekdir(pdir,pos);//设置目录流的读取位置
    pbuf = readdir(pdir);
	printf("%s %d\n",pbuf->d_name, pbuf->d_type);
	closedir(pdir);
	return 0;
}
