#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <sys/types.h>

int (*new_func)(void) = NULL;

int init()
{
    FILE *fp = fopen("/proc/self/maps", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL)
        return -1;

    read = getline(&line, &len, fp);

    char base_address[20];
    strncpy(base_address, line, 12);
    printf("%s\n", base_address);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        fprintf(stdout, "%s", line);
    }
    fclose(fp);

    // if (mprotect(buffer + pagesize * 2, pagesize, PROT_READ) == -1)
    //     handle_error("mprotect");

    long number = (long)strtol(base_address, NULL, 16);

    printf("%lx\n", number);

    void *handle = dlopen("libpoem.so", RTLD_LAZY);
    if (handle != NULL)
    {
        // new_func = dlsym(handle, "code_606");
        new_func = number + 0xdb80;
        printf("new_func = %p\n", new_func);
    }
    new_func();

    // struct codenu
    // char *new_code_606 = base_address + 0x17a30;
    // ndat[606] = 1373;
    // new_code_606[4] = new_code_1373[4];

    return 0;
}
