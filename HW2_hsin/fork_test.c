#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <elf.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>
#include <libelf.h>
#include <gelf.h>
#include <capstone/capstone.h>
int main()
{
    int idx = 0;
    pid_t child = fork();
    if (child == 0)
    {
        while (1)
        {
            // printf("child: %d, idx++: %d\n", child, idx++);
        }
    }
    else if (child > 0)
    {
        pid_t father = getpid();
        printf("parent : %d\n", father);
        while (1)
        {
            // printf("child: %d, idx++: %d\n", child, idx++);
        }
        return 0;
    }
}