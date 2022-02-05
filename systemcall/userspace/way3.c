#include<stdio.h>
#include<sys/types.h>

#include<sys/syscall.h>
#include<errno.h>

int main()
{
	long rc;
	char *file_name = "/home/think/systemcall/way.c";
	unsigned short mode = 0777;
	asm(
		"int $0x80"
		: "=a" (rc)
		: "0" (SYS_chmod), "b" ((long)(file_name)), "c" ((long)(mode))
	);
	if((unsigned long)rc >= (unsigned long)-132)
	{
	    errno = -rc;
	    rc = -1;
	    printf("more \n");
	}
	if(rc == -1)
		printf("error :%d\n",errno);
	else
		printf("success\n");
	return 0;
}
