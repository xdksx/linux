#include<stdio.h>
#include<unistd.h>

#include<sys/syscall.h>
#include<errno.h>


int main()
{
	int rc;
	rc = syscall(SYS_chmod,"test.c",0777);
	if(rc == -1)
	{
		printf("error to set:%d\n",errno);
	}
	else
		printf("success");
	return 0;
}
