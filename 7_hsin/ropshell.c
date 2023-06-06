/*
 * Lab problem set for UNIX programming course
 * by Chun-Ying Huang <chuang@cs.nctu.edu.tw>
 * License: GPLv2
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define errquit(m) { perror(m); exit(-1); }  // 定義錯誤退出宏

#define LEN_CODE  (10 * 0x10000)  // 代碼區域大小
#define LEN_STACK 8192            // 堆疊區域大小

#define TIMEOUT   60              // 執行超時時間（秒）

void shell(char *stack, int slen) {
    int n;

    alarm(TIMEOUT);  // 設置執行超時

    printf("\nshell> ");  // 輸出提示符

    if ((n = read(0, stack + (LEN_STACK / 2), LEN_STACK / 2)) < 0) errquit("read");  
	// ssize_t read(int fd, void *buf, size_t count);

    printf("# %d bytes command received.\n", n);  // 輸出接收到的命令的字節數

    asm volatile (
        "mov %0, %%rsp\n"  // 將堆疊指標rsp設置為指定的地址%0
        "xor %%rax, %%rax\n"  // 將寄存器 rax 清零
        "xor %%rbx, %%rbx\n"  // 將寄存器 rbx 清零
        "xor %%rcx, %%rcx\n"  // 將寄存器 rcx 清零
        "xor %%rdx, %%rdx\n"  // 將寄存器 rdx 清零
        "xor %%rdi, %%rdi\n"  // 將寄存器 rdi 清零
        "xor %%rsi, %%rsi\n"  // 將寄存器 rsi 清零
        "xor %%rbp, %%rbp\n"  // 將寄存器 rbp 清零
        "xor %%r8,  %%r8\n"   // 將寄存器 r8 清零
        "xor %%r9,  %%r9\n"   // 將寄存器 r9 清零
        "xor %%r10, %%r10\n"  // 將寄存器 r10 清零
        "xor %%r11, %%r11\n"  // 將寄存器 r11 清零
        "xor %%r12, %%r12\n"  // 將寄存器 r12 清零
        "xor %%r13, %%r13\n"  // 將寄存器 r13 清零
        "xor %%r14, %%r14\n"  // 將寄存器 r14 清零
        "xor %%r15, %%r15\n"  // 將寄存器 r15 清零
        "ret\n"              // 返回指令
        :
        : "r" (stack + (LEN_STACK / 2))  // 輸入操作數，將buf指標傳入
    );
}


int main() {
    char *code, *stack;
    uint32_t *codeint;
    long i, t;

    setvbuf(stdin,  NULL, _IONBF, 0);    // 禁用標準輸入的緩衝
    setvbuf(stdout, NULL, _IONBF, 0);    // 禁用標準輸出的緩衝
    setvbuf(stderr, NULL, _IONBF, 0);    // 禁用標準錯誤輸出的緩衝

    code = mmap(NULL, LEN_CODE, PROT_READ | PROT_WRITE | PROT_EXEC,
                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);   // 分配可讀、可寫、可執行的記憶體空間
    if (code == MAP_FAILED) errquit("mmap");  // 若分配失敗則退出程式
    codeint = (uint32_t*) code;  // 將分配的記憶體轉換為 uint32_t 指標型別

    stack = mmap(NULL, LEN_STACK, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);  // 分配可讀、可寫的堆疊記憶體空間
    if (stack == MAP_FAILED) errquit("mmap");  // 若分配失敗則退出程式

    memset(stack, 0, LEN_STACK);  // 將堆疊記憶體空間初始化為零
    t = time(0);  // 取得當前時間
    srand(t);  // 使用時間作為隨機種子
    for (i = 0; i < LEN_CODE / 4; i++) {
        codeint[i] = (rand() << 16) | (rand() & 0xffff);  // 在代碼區域隨機生成指令
        printf("%x\n", codeint[i]);
    }
    codeint[rand() % (LEN_CODE / 4 - 1)] = 0xc3050f;  // 將隨機選擇的位置設置為 ret+syscall (little-endian)
    if (mprotect(code, LEN_CODE, PROT_READ | PROT_EXEC) < 0) errquit("mprotect");  // 設置代碼區域為只讀、可執行

    printf("a,%x\n", codeint[3351]);  // 輸出代碼區域指定位置的值
    printf("** Timestamp is %lu\n", t);  // 輸出時間戳
    printf("** Random bytes generated at %p\n", code);  // 輸出隨機數生成的記憶體地址
    printf("** Runtime limitation is %d second(s)\n", TIMEOUT);  // 輸出執行時限

    alarm(TIMEOUT);

	while (1) {
		int st, pid = fork();  // 建立子進程
		if (pid == 0) {  // 子進程執行以下操作
			shell(stack, LEN_STACK);  // 呼叫 shell 函式，傳遞堆疊記憶體和堆疊長度作為參數
			exit(0);  // 子進程執行完畢後退出
		}
		if (waitpid(pid, &st, 0) < 0)  // 等待子進程結束
			// pid_t waitpid(pid_t pid, int *status, int options)
			break;  // 若等待失敗則跳出迴圈
		if (WIFEXITED(st)) {  // 判斷子進程是否正常結束
			printf("** CMD: terminated with exit code %d\n", WEXITSTATUS(st));  // 輸出子進程的退出碼
		} else if (WIFSIGNALED(st)) {  // 判斷子進程是否因訊號結束
			printf("** CMD: signaled with term signal %d\n", WTERMSIG(st));  // 輸出子進程被終止的訊號編號
		} else {
			printf("** CMD: terminated with unhandled state\n");  // 輸出子進程結束時的未處理狀態
		}
	}

	return 0;
}
