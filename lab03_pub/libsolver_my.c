// #include <stdio.h>
// #include <stdlib.h>
// #include <dlfcn.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <string.h>
// #include <sys/mman.h>
// #include "shuffle.h"

// #define NUM_CODES 1477
// typedef int (*code_fn)();

// int init() {
//     printf("Hi 00000");
//     int i;
//     void *handle;
//     code_fn code_fns[NUM_CODES];

//     // Load the runtime library
//     handle = dlopen("./libpoem.so", RTLD_LAZY);
//     if (!handle) {
//         fprintf(stderr, "%s\n", dlerror());
//         exit(1);
//     }
//     printf("Hi 11111");

//     // Determine the page size of the system
//     long page_size = sysconf(_SC_PAGE_SIZE);

//     // Retrieve the addresses of the code functions and the GOT table entries
//     for (i = 0; i < NUM_CODES; i++) {
//         // find objective
//         char str_num[4];sprintf(str_num, "%d", ndat[i]);
//         // itoa(ndat[i], str_num, 4);
//         char *fn_name = "code_";strcat(fn_name,str_num);
//         code_fns[i] = dlsym(handle, fn_name);
//         // code_fns[1] = (code_fn)dlsym(handle,"code_498");

//         // Get the address of the GOT entry of objective
//         unsigned long* got_entry = (unsigned long*)&code_fns[i];
//         // printf("Original GOT entry of my_function: %p\n", (void*)*got_entry);

//         // calculate destination
//         char str_num_transto[4];sprintf(str_num_transto, "%d", ndat[i]);
//         // itoa(i, str_num_transto, 4);
//         char *fn_name_transto = "code_";strcat(fn_name_transto,str_num_transto);
//         code_fn code_fns_transto = dlsym(handle, fn_name_transto);
        
//         printf("Hi 22222");

//         // Calculate the address of the page containing the GOT entry
//         unsigned long page_start = (unsigned long)got_entry & ~(page_size - 1);

//         // Mark the page as writable
//         mprotect((void*)page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
        
//         printf("Hi 33333");

//         // Modify the GOT entry
//         *got_entry = (unsigned long)code_fns_transto;

//         mprotect((void*)page_start, page_size, PROT_READ | PROT_EXEC);
//     }
//     // Close the shared library
//     dlclose(handle);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include "shuffle.h"

#define NUM_CODES 1477

typedef int (*code_fn)();

int init() {
    printf("Hi 00000");
    int i;
    void *handle;
    code_fn code_fns[NUM_CODES];

    // Load the runtime library
    handle = dlopen("./libpoem.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    printf("Hi 11111");

    // Determine the page size of the system
    long page_size = sysconf(_SC_PAGE_SIZE);

    // Retrieve the addresses of the code functions and the GOT table entries
    for (i = 0; i < NUM_CODES; i++) {
        // find objective
        char str_num[5] = {0};
        sprintf(str_num, "%04d", ndat[i]);

        char fn_name[10] = "code_";
        strcat(fn_name, str_num);
        code_fns[i] = dlsym(handle, fn_name);

        // Get the address of the GOT entry of objective
        unsigned long* got_entry = (unsigned long*)&code_fns[i];

        char str_num_transto[5] = {0};
        sprintf(str_num_transto, "%04d", i);

        char fn_name_transto[10] = "code_";
        strcat(fn_name_transto, str_num_transto);
        code_fn code_fns_transto = dlsym(handle, fn_name_transto);

        printf("Hi 22222");

        // Calculate the address of the page containing the GOT entry
        unsigned long page_start = (unsigned long)got_entry & ~(page_size - 1);

        // Mark the page as writable and executable
        mprotect((void*)page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);

        // Modify the GOT entry
        *got_entry = (unsigned long)code_fns_transto;

        mprotect((void*)page_start, page_size, PROT_READ | PROT_EXEC);
    }
    // Close the shared library
    dlclose(handle);
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <dlfcn.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <string.h>
// #include <sys/mman.h>
// #include "shuffle.h"

// #define NUM_CODES 1477
// // #define BASE_ADDR 0x55c487240000
// // #define MAIN_ADDR 0x55c4872507a9
// typedef int (*code_fn)();

// // void reverse(char* str) {
// //     int i, j;
// //     for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
// //         char temp = str[i];
// //         str[i] = str[j];
// //         str[j] = temp;
// //     }
// // }

// // void itoa(int num, char* buf, int base) {
// //     int i = 0;
// //     int is_negative = 0;
// //     if (num == 0) {
// //         buf[i++] = '0';
// //         buf[i] = '\0';
// //         return;
// //     }
// //     if (num < 0 && base == 10) {
// //         is_negative = 1;
// //         num = -num;
// //     }
// //     while (num != 0) {
// //         int remainder = num % base;
// //         buf[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
// //         num /= base;
// //     }
// //     if (is_negative) {
// //         buf[i++] = '-';
// //     }
// //     buf[i] = '\0';
// //     reverse(buf);
// // }


// int init() {
//     printf("Hi 00000");
//     int i;
//     void *handle;
//     code_fn code_fns[NUM_CODES];
//     // unsigned long got_offset[NUM_CODES];
//     // unsigned long symbol_offset[NUM_CODES];
//     // unsigned long got_addr, page_size, page_start, page_end;

//     // Load the runtime library
//     handle = dlopen("./libpoem.so", RTLD_LAZY);
//     if (!handle) {
//         fprintf(stderr, "%s\n", dlerror());
//         exit(1);
//     }
//     printf("Hi 11111");

//     // Determine the page size of the system
//     long page_size = sysconf(_SC_PAGE_SIZE);

//     // Retrieve the addresses of the code functions and the GOT table entries
//     for (i = 0; i < NUM_CODES; i++) {
//         // find objective
//         char str_num[4];sprintf(str_num, "%d", ndat[i]);
//         // itoa(ndat[i], str_num, 4);
//         char *fn_name = "code_";strcat(fn_name,str_num);
//         code_fns[i] = dlsym(handle, fn_name);
//         // code_fns[1] = (code_fn)dlsym(handle,"code_498");

//         // Get the address of the GOT entry of objective
//         unsigned long* got_entry = (unsigned long*)&code_fns[i];
//         // printf("Original GOT entry of my_function: %p\n", (void*)*got_entry);

//         // calculate destination
//         char str_num_transto[4];sprintf(str_num_transto, "%d", ndat[i]);
//         // itoa(i, str_num_transto, 4);
//         char *fn_name_transto = "code_";strcat(fn_name_transto,str_num_transto);
//         code_fn code_fns_transto = dlsym(handle, fn_name_transto);
        
//         printf("Hi 22222");


        

//         // Calculate the address of the page containing the GOT entry
//         unsigned long page_start = (unsigned long)got_entry & ~(page_size - 1);

//         // Mark the page as writable
//         mprotect((void*)page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
        
//         printf("Hi 33333");

//         // Modify the GOT entry
//         *got_entry = (unsigned long)code_fns_transto;

//         mprotect((void*)page_start, page_size, PROT_READ | PROT_EXEC);
//     }
//     // Close the shared library
//     dlclose(handle);
//     return 0;
//     // // Calculate the actual addresses of the GOT table entries and make them writable
//     // got_addr = MAIN_ADDR + (got_offset[0] - MAIN_OFFSET);
//     // page_size = sysconf(_SC_PAGE_SIZE);
//     // page_start = got_addr & ~(page_size - 1);
//     // page_end = (got_addr + NUM_CODES * sizeof(unsigned long)) & ~(page_size - 1);
//     // mprotect((void *) page_start, page_end - page_start, PROT_READ | PROT_WRITE);

//     // // Modify the GOT table entries to redirect the function calls
//     // for (i = 0; i < NUM_CODES; i++) {
//     //     unsigned long *got_entry = (unsigned long *) (got_addr + i * sizeof(unsigned long));
//     //     unsigned long symbol_addr = BASE_ADDR + symbol_offset[ndat[i].idx];
//     //     *got_entry = symbol_addr;
//     // }
// }
