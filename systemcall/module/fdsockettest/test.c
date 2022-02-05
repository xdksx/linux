#define _GNU_SOURCE
#include <sys/syscall.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>

#include<sys/types.h>

#include<sys/syscall.h>
#include<errno.h>
#define _NR_new 434
int main(int argc, char *argv[])
{
	long rc;
    //int fds = socket(AF_INET,SOCK_STREAM,0);
    int fds = socket(AF_INET,SOCK_DGRAM,0);
    printf("fds:%d\n",fds);
	//asm(
		//"int $0x80"
	//	: "=a" (rc)
		//: "0" (_NR_new), "b" ((long)(fds))
	//);
     syscall(_NR_new,fds);
    close(fds);
    exit(EXIT_SUCCESS);
}
