#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <string.h>

char* reverseCharArray(char* arr, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        // 交換兩個元素
        char temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        // 移動指標
        start++;
        end--;
    }
    return arr;
}
int main(int argc, char * argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <challenge_executable>\n", argv[0]);
        return 1;
    }
    pid_t child;
    int status;
    struct user_regs_struct regs;

    if((child = fork()) < 0){
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    } else if (child == 0) {
        // Child process
        long ret;
        if (ret = ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
            fprintf(stderr, "Ptrace: PTRACE_TRACEME error\n");
        }
        // printf("ret: %ld\n",ret);
        execlp(argv[1], argv[1], NULL);
        // printf("Child Finished\n");
    } else if (child > 0) {
        // Attach to the child process
        // ptrace(PTRACE_ATTACH, child, NULL, NULL);

        // Wait for the child to stop after being execlp-ed
        wait(&status);
        ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_EXITKILL);
        ptrace(PTRACE_CONT, child, NULL, NULL);
        // printf("11111\n");

        
        // Loop to find the correct value for magic
        char magic[9] = {'0','0','0','0','0','0','0','0','0'};
        unsigned long *magic_base = (unsigned long*) magic;
        unsigned long *magic_base8 = (unsigned long*) (magic+8);
        int found = 0;
        unsigned long jmp_bk_rip;
        int cnt = 0;
        // printf("22222\n");

        // Wait for the child to stop after first CC()
        wait(&status);
        ptrace(PTRACE_CONT, child, NULL, NULL);
        // Wait for the child to stop after second CC(), memset() is ready
        wait(&status);
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        // printf("regs.rax: %llx\n", regs.rax);

        // Calculate the address of magic X!
        // 8978:	48 8d 05 49 f8 0c 00 	lea    rax,[rip+0xcf849]        # d81c8 <magic>
        // unsigned long magic_addr = (long unsigned)&regs.rip + 0xcf849;

        // Get the address of magic V!
        unsigned long long data[2];
        // data[0] = ptrace(PTRACE_PEEKTEXT, child, regs.rax, NULL);
        data[0] = regs.rax;
        char* magic_addr = (char*)data[0];
        // printf("data[0]: %llx magic_addr: %p\n", data[0], magic_addr);
        // printf("data[0]: %llx magic_addr: %p *magic_addr: %c\n", data[0], magic_addr, *magic_addr);
        
        // data[1] = ptrace(PTRACE_PEEKDATA, child, regs.rax + 8, NULL);
        data[1] = regs.rax + 8;
        char* magic_addr8 = (char*)data[1];
        // printf("data[1]: %llx magic_addr8: %p \n", data[1], magic_addr8);
        // printf("data[1]: %llx magic_addr8: %p *magic_addr8: %c\n", data[1], magic_addr8, *magic_addr8);
        ptrace(PTRACE_CONT, child, NULL, NULL);


         // Wait for the child to stop after oracle_connect()
        wait(&status);
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        jmp_bk_rip = regs.rip;      // Save the rip of oracle_connect()'s CC()??? 所以預計跳回來時下一行是reset的一開始？？
        ptrace(PTRACE_CONT, child, NULL, NULL);

        while (!found)
        {
            // Increment the magic value
            int index = 0;
            while (index < 8 && magic[index] == '1') {
                magic[index] = '0';
                index++;
            }
            if (index < 8 || (index == 8 && magic[index] == '0')) {
                magic[index] = '1';
            } else {
                printf("Magic value can't find.\n");
                break;
            }
            // printf("magic[%d]: ", cnt++);
            // for(int i=sizeof(magic)-1;i>=0;i--){
            //     printf("%c", magic[i]);
            // }
            // // for(int i=0;i<sizeof(magic);i++){
            // //     printf("%c", magic[i]);
            // // }
            // printf("\n");


            // int index = 0;
            // while (index < 10 && magic[index] == '1') {
            //     magic[index] = '0';
            //     index++;
            // }
            // if (index < 10 || (index == 10 && magic[index] == '0')) {
            //     magic[index] = '1';
            // } else {
            //     printf("Magic value can't find.\n");
            //     break;
            // }
            // for(int i=0;i<sizeof(magic);i++){
            //     printf("%c", magic[i]);
            // }
            // printf("\n");

            // Wait for the child to stop after oracle_reset()
            wait(&status);
             // Update the value of magic
            ptrace(PTRACE_POKETEXT, child, magic_addr, *magic_base);
            unsigned char byte = (*magic_base8 & 0xFF);
            ptrace(PTRACE_POKETEXT, child, magic_addr8, byte);  //單獨寫入第九個byte,其餘10-15byte都保持0
            // ptrace(PTRACE_POKETEXT, child, magic_addr8, (*magic_base8 & 0x00000000000000FF));  //單獨寫入第九個byte,其餘10-15byte都保持0
            ptrace(PTRACE_CONT, child, NULL, NULL);

            // Wait for the child to stop after oracle_update() & oracle_get_flag()
            wait(&status);
            ptrace(PTRACE_GETREGS, child, NULL, &regs);
            if(regs.rax == 0x0){
                // printf("Magic value found: %s\n", reverseCharArray(magic, sizeof(magic)));
                found = 1;

                ptrace(PTRACE_CONT, child, NULL, NULL);

                // Wait for the child to stop after printf("Magic evaluated: %s\n", magic);
                wait(&status);
                ptrace(PTRACE_CONT, child, NULL, NULL);
                break;
            } else {
                // printf("Magic value not found.\n");
                regs.rip = jmp_bk_rip;
                ptrace(PTRACE_SETREGS, child, NULL, &regs);
                ptrace(PTRACE_CONT, child, NULL, NULL);
            }
        }  
        // Detach from the traced process
        // ptrace(PTRACE_DETACH, child, NULL, NULL);
        // printf("Parent Finished First\n");
    }
    return 0;
}
