#define _GNU_SOURCE
#include <sys/syscall.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = syscall(546, "hello.txt", O_RDWR|O_CREAT, 0777);

    exit(EXIT_SUCCESS);
}
