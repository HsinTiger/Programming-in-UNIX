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
#define disassemble_Ins_cnt 5
#define parsing_code_size 40

static Elf64_Addr Child_entryPoint;
static ssize_t text_sec_size;
static unsigned char *text_sec_data = NULL;
static unsigned long *text_sec = NULL;

// store each anchor
typedef struct RCAE_info{
    unsigned long RCAE_address;
    struct RCAE_info* next;
} RCAE_content;
RCAE_content *restore_CC_after_exec_head = NULL;
RCAE_content* create_RCAE(unsigned long RCAE_address)
{
    RCAE_content *new_RCAE = (RCAE_content *)malloc(sizeof(RCAE_content));
    new_RCAE->RCAE_address = RCAE_address;
    printf("new_RCAE->RCAE_address: %lx\n", new_RCAE->RCAE_address);
    new_RCAE->next = NULL;
    return new_RCAE;
}
void Insert_RCAE(RCAE_content *new_RCAE)
{
    RCAE_content *current = restore_CC_after_exec_head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_RCAE;
}


// store each anchor
typedef struct anchor_info{
    int cnt;
    unsigned long *start, *end;   //unsigned long start[10], end[10];
    unsigned long **anchor_memory;
    struct user_regs_struct anchor_regs;
    bool used_flag;
} anchor_content;

static anchor_content anchor_content_self;
// static bool time_travel_flag = false;

// store address & visited flag
typedef struct bp{
    unsigned long address;
    bool visited;
    unsigned long *replaced_ins;
    struct bp *next;
} break_point_t;
static break_point_t *break_point_head = NULL; // inintial until the main

void Insert_bp(break_point_t *newNode)
{
    break_point_t *current = break_point_head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}
void Delete_specific_bp(unsigned long address)
{
    break_point_t *current = break_point_head;
    break_point_t *previous = NULL;

    while (current != NULL && current->address != address)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        // Node with given value not found
        printf("Can't fond the bp node.\n");
    }
    else if (previous == NULL)
    {
        // Node to be deleted is the head node
        break_point_head = current->next;
        free(current);
    }
    else
    {
        // Node to be deleted is in the middle or end
        previous->next = current->next;
        free(current);
    }
}
break_point_t *Visit_specific_bp(unsigned long address)
{
    break_point_t *current = break_point_head;
    break_point_t *previous = NULL;

    while (current != NULL && current->address != address)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        // Node with given value not found
        printf("Can't fond the bp node.\n");
        return NULL;
    }
    else
    {
        printf("fond the bp node, address is %lx.\n", current->address);
        if (!current->visited)
            current->visited = true;
        return current;
    }
}

static char *cmds[5] = {
    "si",
    "cont",
    "break",
    "anchor",
    "timetravel"};
char *reverseCharArray(char *arr, int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
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

void eraseChars(char *str, const char *charsToRemove)
{
    int i, j;
    int len = strlen(charsToRemove);
    int strLen = strlen(str);
    int k = 0;

    for (i = 0; i < strLen; ++i)
    {
        int removeChar = 0;
        for (j = 0; j < len; ++j)
        {
            if (str[i] == charsToRemove[j])
            {
                removeChar = 1;
                break;
            }
        }

        if (!removeChar)
        {
            str[k++] = str[i];
        }
    }
    str[k] = '\0'; // Add the null terminator at the end of the new string
}

// Function to disassemble instructions given the binary representation
// void disassembleInstructions(void *address, size_t count, Elf64_Addr firstInsPoint)
void disassembleInstructions(void *address, size_t count, Elf64_Addr firstInsPoint, size_t code_size)
{
    csh cshandle;
    cs_insn *insn;
    size_t count_disassembled;
    if (cs_open(CS_ARCH_X86, CS_MODE_64, &cshandle) != CS_ERR_OK)
    {
        fprintf(stderr, "Failed to initialize Capstone disassembler\n");
        exit(EXIT_FAILURE);
    }
    cs_option(cshandle, CS_OPT_DETAIL, CS_OPT_ON);

    // count_disassembled = cs_disasm(cshandle, address, text_sec_size, (uint64_t)address, 0, &insn);
    count_disassembled = cs_disasm(cshandle, address, code_size, (uint64_t)address, 0, &insn);
    unsigned long base_addr_offset = (unsigned long)firstInsPoint - (unsigned long)insn[0].address;

    // if (count_disassembled > 0) {
    for (size_t i = 0; i < count; ++i)
    {
        // if (insn[i].address + insn[i].size <= (unsigned long)text_sec_data + text_sec_size)

        // printf("insn[i].address:%lx\n", insn[i].address);
        // printf("insn[i].size:%lx\n", insn[i].size);
        // printf("Child_entryPoint:%lx\n", Child_entryPoint);
        // printf("text_sec_size:%lx\n", text_sec_size);

        // if (insn[i].address + insn[i].size <= (unsigned long)Child_entryPoint + text_sec_size)
        // printf("accumulated_size:%lx\n", accumulated_size);

        // if (insn[i].address + base_addr_offset < (unsigned long)Child_entryPoint + text_sec_size)
        
        
        
        // if (( long)address < ( long)text_sec || ( long)address > ( long)text_sec + text_sec_size){
        if (( long)address < ( long)Child_entryPoint || ( long)address > ( long)Child_entryPoint + text_sec_size){
                printf("\t%" PRIx64 ": ", insn[i].address + base_addr_offset); //!!!

                for (size_t j = 0; j < insn[i].size; ++j)
                {
                    unsigned long idx = (unsigned long)insn[i].address - (unsigned long)address + j;
                    char *byte_code = (char *)address;
                    // printf("idx:%d\n", idx);
                    printf("%02hhx ", byte_code[idx]);
                }
                if (insn[i].size < 7)
                {
                    for (size_t j = 0; j < 7 - insn[i].size; ++j)
                    {
                        printf("   "); // 3 spaces
                    }
                }
                printf("        "); // 8 spaces
                printf("%-8s %s\n", insn[i].mnemonic, insn[i].op_str);
        } else {
            if (insn[i].address + insn[i].size <= ( long)text_sec + text_sec_size)
            {

                printf("\t%" PRIx64 ": ", insn[i].address + base_addr_offset); //!!!

                for (size_t j = 0; j < insn[i].size; ++j)
                {
                    unsigned long idx = (unsigned long)insn[i].address - (unsigned long)address + j;
                    char *byte_code = (char *)address;
                    // printf("idx:%d\n", idx);
                    printf("%02hhx ", byte_code[idx]);
                }
                if (insn[i].size < 7)
                {
                    for (size_t j = 0; j < 7 - insn[i].size; ++j)
                    {
                        printf("   "); // 3 spaces
                    }
                }
                printf("        "); // 8 spaces
                printf("%-8s %s\n", insn[i].mnemonic, insn[i].op_str);
            }
            else
            {
                printf("** the address is out of the range of the text section.\n");
                break;
            }
        }
    }
    cs_free(insn, count_disassembled);

    // // if (count > count_disassembled){
    // if(insn[cnt-1].address + insn[i].size > (unsigned long)address + text_sec_size){
    //     printf("** the address is out of the range of the text section.\n");
    // }
    cs_close(&cshandle);
}

// Function to obtain the entry point address of the executable
unsigned char *getEntryPointAddress(const char *programPath, ssize_t *size)
{
    int fd;
    Elf *elf;
    Elf_Data *data = NULL;
    unsigned char *buffer = NULL;

    if ((fd = open(programPath, O_RDONLY, 0)) < 0)
    {
        fprintf(stderr, "Failed to open program: %s\n", programPath);
        exit(EXIT_FAILURE);
    }

    if (elf_version(EV_CURRENT) == EV_NONE)
    {
        fprintf(stderr, "Failed to initialize libelf\n");
        exit(EXIT_FAILURE);
    }

    if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
    {
        fprintf(stderr, "Failed to initialize libelf\n");
        exit(EXIT_FAILURE);
    }

    if (elf_kind(elf) != ELF_K_ELF)
    {
        fprintf(stderr, "Not an ELF object\n");
        exit(EXIT_FAILURE);
    }

    Elf_Scn *section = NULL;
    GElf_Shdr sectionHeader;
    // Obtain the section string table index
    size_t sectionStrIdx;
    if (elf_getshdrstrndx(elf, &sectionStrIdx) != 0)
    {
        fprintf(stderr, "Failed to retrieve section string table index\n");
        exit(EXIT_FAILURE);
    }
    while ((section = elf_nextscn(elf, section)) != NULL)
    {
        if (gelf_getshdr(section, &sectionHeader) != &sectionHeader)
        {
            fprintf(stderr, "Failed to retrieve section header\n");
            exit(EXIT_FAILURE);
        }

        // Find the section containing the entry point information (e.g., .text)
        if (strcmp(elf_strptr(elf, sectionStrIdx, sectionHeader.sh_name), ".text") == 0)
        {
            // Read the section data
            data = elf_getdata(section, NULL);
            if (data == NULL)
            {
                fprintf(stderr, "Failed to read section data: %s\n", elf_errmsg(-1));
                exit(EXIT_FAILURE);
            }

            // Allocate memory for the buffer
            buffer = (unsigned char *)malloc(data->d_size);
            memset(buffer, 0, data->d_size);
            if (buffer == NULL)
            {
                fprintf(stderr, "Failed to allocate memory\n");
                exit(EXIT_FAILURE);
            }

            // Copy the section data to the buffer
            memcpy(buffer, data->d_buf, data->d_size);
            *size = data->d_size;

            // *entry_point = sectionHeader.sh_addr;
            elf_end(elf);
            close(fd);
            return buffer;
        }
    }
    fprintf(stderr, "Entry point section not found\n");
    exit(EXIT_FAILURE);
}
unsigned long *get_by_peektext(pid_t child, unsigned long Child_rip, ssize_t code_size)
{
    // 改peektext child process .text的內容，而非從elf拿
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, child, NULL, &regs);

    // Allocate memory for the buffer
    unsigned long *buffer = (unsigned long *)malloc(code_size);
    memset(buffer, 0, code_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    int len;
    if (code_size % 8 != 0)
        len = code_size / 8 + 1;
    else 
        len = code_size / 8;
    for (int i = 0; i < len; i++)
    {
        buffer[i] = ptrace(PTRACE_PEEKTEXT, child, Child_rip + i * 8, NULL);
        // printf("buffer[%d]: %lx\n", i, buffer[i]);
    }
    return buffer;
}

int main(int argc, char *argv[])
{
    char *launch_cmd = (char *)malloc(sizeof(char) * 50);
    if (argc < 2)
    {
        fprintf(stderr, "<Please indicate the objective executeable>\n");
        fprintf(stderr, "Usage: %s <objective executeable>\n", argv[0]);
        return 1;
    }
    //     printf("Child process is ready to be traced,\n\
// Please indicate the specific user command to start.\n");
    // while (fgets(launch_cmd, sizeof(launch_cmd), stdin) &&
    //        (launch_cmd[strcspn(launch_cmd, "\n")] = '\0') && (strcmp(launch_cmd, cmds[0]) != 0 && strcmp(launch_cmd, cmds[1]) != 0))
    // {
    //     printf("Your command : %s\n", launch_cmd);
    //     printf("Please indicate the right user command to start.\n");
    // }

    // launch the tracee program
    pid_t child;

    if ((child = fork()) < 0)
    {
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    }
    else if (child == 0)
    {
        long ret;
        if (ret = ptrace(PTRACE_TRACEME, 0, 0, 0) < 0)
        {
            fprintf(stderr, "Ptrace: PTRACE_TRACEME error\n");
        }
        // execlp(argv[1], argv[1], NULL);
        execvp(argv[1], argv + 1); // 待執行檔必須要是exe mode,不然可以透過execvp的ret value來判斷
    }
    else if (child > 0)
    {
        int status = 0;

        anchor_content_self.used_flag = false;

        // Wait for the child to stop after being execlp-ed
        pid_t wait_exe_child;
        if (wait_exe_child = waitpid(child, &status, 0) == -1)
        {
            fprintf(stderr, "Ptrace: waitpid error\n");
        }
        // printf("wait_exe_child: %d\nstatus: %d\n",wait_exe_child, status);
        ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_EXITKILL);
        ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACEFORK);

        // Check the status of the child process
        if (WIFEXITED(status))
        {
            // printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            // printf("Child process terminated by signal: %d\n", WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            // printf("Child process stopped by signal: %d\n", WSTOPSIG(status));

            // *首先從/proc/child/exe中獲取運行時程序的內存地址
            char *child_exe = malloc(sizeof(char) * 20);
            // sprintf(child_exe, "ls /proc/%d/", child);
            // system(child_exe);

            // *Obtain the entry point address using libelf, and copy the .text section to buffer
            sprintf(child_exe, "/proc/%d/exe", child);
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, child, NULL, &regs);
            printf("** program '%s' loaded. entry point 0x%lx\n", argv[1], (unsigned long)regs.rip);
            Child_entryPoint = (unsigned long)regs.rip;

            text_sec_data = getEntryPointAddress(child_exe, &text_sec_size);
            // printf("** program '%s' loaded. entry point 0x%lx\n", argv[1], (unsigned long)Child_entryPoint);

            // *且一次PEEK拿一整份來備份
            text_sec = get_by_peektext(child, (unsigned long)regs.rip, text_sec_size);
            disassembleInstructions((void *)text_sec, disassemble_Ins_cnt, (unsigned long)regs.rip, parsing_code_size);
            // *Disassemble instructions starting from the current program counter (RIP)
            // *改peektext child process .text的內容，而非從elf拿
            // unsigned long *buffer = get_by_peektext(child, (unsigned long)regs.rip, parsing_code_size);
            // disassembleInstructions((void *)buffer, disassemble_Ins_cnt, (unsigned long)regs.rip, parsing_code_size);

            // disassembleInstructions((void *)text_sec_data, disassemble_Ins_cnt, Child_entryPoint);

            char user_cmd[100];
            
            while (printf("(sdb)"))
            {
                memset(user_cmd, sizeof(user_cmd), 0);
                fgets(user_cmd, sizeof(user_cmd), stdin);
                user_cmd[strcspn(user_cmd, "\n")] = '\0';
                // printf("user_cmd:%s\n", user_cmd);

                struct user_regs_struct regs;

                // si與cont不同，si在踩到bp前就提早預報了
                if (strcmp(user_cmd, cmds[0]) == 0)
                {
                    ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
                    waitpid(child, &status, 0);
                    if (WIFEXITED(status) || WIFSIGNALED(status))
                    {
                        printf("** the target program terminated.\n");
                        break;
                    }

                    // if (time_travel_flag == false) {
                        // if (restore_CC_after_exec)
                        // {
                        //     // 執行完該行bp的指令後，將該CC再次恢復
                        //     printf("restore_CC_after_exec begin\n");
                        //     unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, restore_CC_after_exec, 0);
                        //     printf("now_the_ins: %lx\n", now_the_ins);
                        //     // recover_ins
                        //     printf("restore_CC_after_exec end: %lx\n", (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);
                        //     ptrace(PTRACE_POKETEXT, child, restore_CC_after_exec, (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);
                        // }

                        // timetravel 後，要把anchor加回CC, bp加在rip上也要延遲加回CC
                        while (restore_CC_after_exec_head) {
                            printf("restore_CC_after_exec_head begin\n");
                            unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, restore_CC_after_exec_head->RCAE_address, 0);
                            printf("now_the_ins: %lx\n", now_the_ins);
                            // recover_ins
                            printf("restore_CC_after_exec_head end: %lx\n", (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);
                            ptrace(PTRACE_POKETEXT, child, restore_CC_after_exec_head->RCAE_address, (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);

                            RCAE_content *current = restore_CC_after_exec_head;
                            restore_CC_after_exec_head = restore_CC_after_exec_head->next;
                            free(current);
                        }

                        ptrace(PTRACE_GETREGS, child, NULL, &regs);
                        break_point_t *visited_Node = NULL;
                        if ((visited_Node = Visit_specific_bp(regs.rip)) != NULL) // stop due to int3(CC)
                        {
                            printf("** hit a breakpoint at 0x%llx.\n", regs.rip);
                            unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, regs.rip, 0);
                            // printf("now_the_ins: %lx\n", now_the_ins);
                            // recover_ins
                            // printf("recover_ins: %lx\n", *(visited_Node->replaced_ins));

                            // * find the CC in the unsigned long's tail
                            printf("recover_ins: %lx\n", (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            ptrace(PTRACE_POKETEXT, child, regs.rip, (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            // ptrace(PTRACE_POKETEXT, child, regs.rip, *(visited_Node->replaced_ins));

                            if(restore_CC_after_exec_head == NULL){
                                restore_CC_after_exec_head = create_RCAE(regs.rip);
                            } else {
                                Insert_RCAE(create_RCAE(regs.rip));
                            }
                        }
                        // si:rip-1 有兩個時機,一個timetravel,一個是第一行
                        // cont:rip-1 只需考慮timetravel


                        // eislse if ((vited_Node = Visit_specific_bp(regs.rip - 1)) != NULL && regs.rip - 1 == Child_entryPoint)
                        // {
                        //     // stop due to int3(CC) 且 bp設在第一行程式一開始的地方
                        //     printf("** hit a breakpoint at 0x%llx.\n", regs.rip - 1);
                        //     unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, regs.rip - 1, 0);
                        //     printf("now_the_ins: %lx\n", now_the_ins);
                        //     // recover_ins
                        //     printf("recover_ins: %lx\n", *(visited_Node->replaced_ins));
                        //     ptrace(PTRACE_POKETEXT, child, regs.rip - 1, *(visited_Node->replaced_ins));

                        //     // 用regs.rip-1去我們提早拷貝的原版text_sec_data找到對應的指令，並且disassemble
                        //     regs.rip = regs.rip - 1;

                        //     printf("RIP-1: 0x%llx\n", regs.rip);

                        //     if(restore_CC_after_exec_head == NULL){
                        //         restore_CC_after_exec_head = create_RCAE(regs.rip);
                        //     } else {
                        //         Insert_RCAE(create_RCAE(regs.rip));
                        //     }
                        //     // restore_CC_after_exec = regs.rip;
                        //     ptrace(PTRACE_SETREGS, child, NULL, &regs);
                        // }


                        // 去我們提早拷貝的原版text_sec_data找到對應的指令，並且disassemble
                        printf("RIP: 0x%llx\n", regs.rip);
                         long _offset = ( long)regs.rip - ( long)Child_entryPoint;
                        printf("offset: 0x%lx\n", _offset);
                        // unsigned long _cal_address = (unsigned long)text_sec_data + _offset;
                         long _cal_address = ( long)text_sec + _offset;
                        printf("cal_address: 0x%lx\n", _cal_address);


                        if (_cal_address < ( long)text_sec || _cal_address > ( long)text_sec + text_sec_size)
                        {
                            // printf("** the address is out of the range of the text section.\n");
                            unsigned long* get_five_row;
                            get_five_row = malloc(sizeof(unsigned long) * 5);
                            for(int i=0;i<5;i++){
                                get_five_row[i] = ptrace(PTRACE_PEEKTEXT, child, regs.rip + i * 8, NULL);
                                break_point_t *visited_Node = NULL;
                                if ((visited_Node = Visit_specific_bp(regs.rip + i*8)) != NULL) // stop due to int3(CC)
                                {
                                    get_five_row[i] = *(visited_Node->replaced_ins);
                                }
                                // // 判斷get_five_row裡有沒有CC 要找出換成原本的指令
                                // char* offset = strstr(get_five_row[i], "CC");
                                // if(offset != NULL){
                                //     printf("offset: %s\n", offset);
                                // }
                                // get_five_row[i] = 

                            }
                            // break_point_t *visited_Node = NULL;
                            // if ((visited_Node = Visit_specific_bp(regs.rip + i)) != NULL) // stop due to int3(CC)
                            // {
                            

                            //     // * find the CC in the unsigned long's tail
                            //     printf("recover_ins: %lx\n", (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            //     ptrace(PTRACE_POKETEXT, child, regs.rip, (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            //     // ptrace(PTRACE_POKETEXT, child, regs.rip, *(visited_Node->replaced_ins));
                            // }

                            // // 判斷get_five_row裡有沒有CC 要找出換成原本的指令
                            // char* get_five_row_char = (char*)get_five_row;
                            // for(int i=0;i<40;i++){
                            //     char* offset = strstr(get_five_row_char[i], "C");
                            //     if(offset != NULL){
                            //         printf("offset: %s\n", offset);
                            //     }
                            //     if(get_five_row_char[i] == "C"){
                            //         get_five_row_char[i] = 
                            //     }
                                
                            // }
                            
                            
                            
                            disassembleInstructions((void *)get_five_row, disassemble_Ins_cnt, (unsigned long)regs.rip, parsing_code_size);
                        } else {
                            // *Disassemble instructions starting from the current program counter (RIP)
                            // *改peektext child process .text的內容，而非從elf拿
                            disassembleInstructions((void *)_cal_address, disassemble_Ins_cnt, (unsigned long)regs.rip, parsing_code_size);
                        }

                        
                }
                else if (strcmp(user_cmd, cmds[1]) == 0)
                {
                    ptrace(PTRACE_GETREGS, child, NULL, &regs);
                    unsigned long _si_addr = (unsigned long)regs.rip;
                    ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
                    waitpid(child, &status, 0);
                    if (WIFEXITED(status) || WIFSIGNALED(status))
                    {
                        printf("** the target program terminated.\n");
                        break;
                    }
                    break_point_t *visited_Node = NULL;
                    if ((visited_Node = Visit_specific_bp(_si_addr)) != NULL){ // stop due to int3(CC)
                        // 需延遲Insert CC
                        // unsigned long insert_CC = (*(visited_Node->replaced_ins) & 0xFFFFFFFFFFFFFF00) | 0xCC;
                        // printf("delay insert_CC: %lx\n", insert_CC);
                        // ptrace(PTRACE_POKETEXT, child, address, insert_CC);
                        printf("New_Node->address: %lx\n", visited_Node->address);
                        if(restore_CC_after_exec_head == NULL){
                            restore_CC_after_exec_head = create_RCAE(visited_Node->address);
                        } else {
                            Insert_RCAE(create_RCAE(visited_Node->address));
                        }
                    }
                    
                    // if (time_travel_flag == false){
                    // if (restore_CC_after_exec)
                    // {
                    //     // 執行完該行bp的指令後，將該CC再次恢復
                    //     printf("restore_CC_after_exec begin\n");
                    //     unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, restore_CC_after_exec, 0);
                    //     printf("now_the_ins: %lx\n", now_the_ins);
                    //     // recover_ins
                    //     printf("restore_CC_after_exec end: %lx\n", (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);
                    //     ptrace(PTRACE_POKETEXT, child, restore_CC_after_exec, (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);
                    // }
                    while (restore_CC_after_exec_head) {
                        printf("restore_CC_after_exec_head begin\n");
                        unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, restore_CC_after_exec_head->RCAE_address, 0);
                        printf("now_the_ins: %lx\n", now_the_ins);
                        // recover_ins
                        printf("restore_CC_after_exec_head end: %lx\n", (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);
                        ptrace(PTRACE_POKETEXT, child, restore_CC_after_exec_head->RCAE_address, (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);

                        RCAE_content *current = restore_CC_after_exec_head;
                        restore_CC_after_exec_head = restore_CC_after_exec_head->next;
                        free(current);
                    }


                    ptrace(PTRACE_CONT, child, NULL, NULL);
                    waitpid(child, &status, 0);
                    if (WIFEXITED(status) || WIFSIGNALED(status))
                    {
                        printf("** the target program terminated.\n");
                        break;
                    } 

                    ptrace(PTRACE_GETREGS, child, NULL, &regs);
                    
                    if ((visited_Node = Visit_specific_bp(regs.rip - 1)) != NULL) // stop due to int3(CC)
                    {
                        printf("** hit a breakpoint at 0x%llx.\n", regs.rip - 1);
                        unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, regs.rip - 1, 0);
                        printf("now_the_ins: %lx\n", now_the_ins);
                        // recover_ins
                        printf("recover_ins: %lx\n", *(visited_Node->replaced_ins));

                        // * find the CC in the unsigned long's tail
                        ptrace(PTRACE_POKETEXT, child, regs.rip - 1, (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                        // ptrace(PTRACE_POKETEXT, child, regs.rip - 1, *(visited_Node->replaced_ins));

                        // 用regs.rip-1去我們提早拷貝的原版text_sec_data找到對應的指令，並且disassemble
                        printf("RIP-1: 0x%llx\n", regs.rip - 1);
                         long _offset = ( long)(regs.rip - 1) - ( long)Child_entryPoint;
                        printf("offset: 0x%lx\n", _offset);
                        // unsigned long _cal_address = (unsigned long)text_sec_data + _offset;
                         long _cal_address = ( long)text_sec + _offset;
                        printf("cal_address: 0x%lx\n", _cal_address);

                        // *Disassemble instructions starting from the current program counter (RIP)
                        // *改peektext child process .text的內容，而非從elf拿
                        if (_cal_address < ( long)text_sec || _cal_address > ( long)text_sec + text_sec_size)
                        {
                            // printf("** the address is out of the range of the text section.\n");
                            unsigned long* get_five_row;
                            get_five_row = malloc(sizeof(unsigned long) * 5);
                            for(int i=0;i<5;i++){
                                get_five_row[i] = ptrace(PTRACE_PEEKTEXT, child, regs.rip-1 + i * 8, NULL);
                                break_point_t *visited_Node = NULL;
                                if ((visited_Node = Visit_specific_bp(regs.rip -1  + i*8)) != NULL) // stop due to int3(CC)
                                {
                                    get_five_row[i] = *(visited_Node->replaced_ins);
                                }
                                // // 判斷get_five_row裡有沒有CC 要找出換成原本的指令
                                // char* offset = strstr(get_five_row[i], "CC");
                                // if(offset != NULL){
                                //     printf("offset: %s\n", offset);
                                // }
                                // get_five_row[i] = 

                            }
                            // break_point_t *visited_Node = NULL;
                            // if ((visited_Node = Visit_specific_bp(regs.rip + i)) != NULL) // stop due to int3(CC)
                            // {
                            

                            //     // * find the CC in the unsigned long's tail
                            //     printf("recover_ins: %lx\n", (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            //     ptrace(PTRACE_POKETEXT, child, regs.rip, (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            //     // ptrace(PTRACE_POKETEXT, child, regs.rip, *(visited_Node->replaced_ins));
                            // }
                            
                            // // 判斷get_five_row裡有沒有CC 要找出換成原本的指令
                            // char* get_five_row_char = (char*)get_five_row;
                            // for(int i=0;i<40;i++){
                            //     char* offset = strstr(get_five_row_char[i], "C");
                            //     if(offset != NULL){
                            //         printf("offset: %s\n", offset);
                            //     }
                            //     if(get_five_row_char[i] == "C"){
                            //         get_five_row_char[i] = 
                            //     }
                                
                            // }
                            
                            
                            
                            disassembleInstructions((void *)get_five_row, disassemble_Ins_cnt, (unsigned long)regs.rip -1, parsing_code_size);
                        } else {
                            // *Disassemble instructions starting from the current program counter (RIP)
                            // *改peektext child process .text的內容，而非從elf拿
                            disassembleInstructions((void *)_cal_address, disassemble_Ins_cnt, (unsigned long)regs.rip -1, parsing_code_size);
                        }
                        // disassembleInstructions((void *)_cal_address, disassemble_Ins_cnt, (unsigned long)regs.rip - 1, parsing_code_size);




                        // unsigned long *buffer = get_by_peektext(child, (unsigned long)regs.rip, parsing_code_size);
                        // disassembleInstructions((void *)buffer, disassemble_Ins_cnt, (unsigned long)regs.rip - 1, parsing_code_size);

                        if(restore_CC_after_exec_head == NULL){
                            restore_CC_after_exec_head = create_RCAE(regs.rip - 1);
                        } else {
                            Insert_RCAE(create_RCAE(regs.rip - 1));
                        }
                        regs.rip = regs.rip - 1;
                        ptrace(PTRACE_SETREGS, child, NULL, &regs);
                    }          
                }
                else if (strstr(user_cmd, cmds[2]) != NULL)
                {
                    // printf("user_cmd:%s\n", user_cmd);
                    char *substr = strstr(user_cmd, "0x");
                    // printf("substr:%s\n", substr);
                    unsigned long address = strtol(substr, NULL, 16);
                    // printf("address:%lx\n", address);

                    ptrace(PTRACE_GETREGS, child, NULL, &regs);

                    // sholud be the last instruction's start address???
                    // if (address - (unsigned long)Child_entryPoint < (unsigned long)text_sec_size && address != regs.rip)
                    if (address != regs.rip)
                    {
                        printf("** set a breakpoint at 0x%lx\n", address);
                        // printf("break_point_t size:%ld\n",sizeof(break_point_t));
                        break_point_t *New_Node = malloc(sizeof(break_point_t));
                        if (New_Node == NULL)
                        {
                            fprintf(stderr, "Failed to allocate memory\n");
                            exit(EXIT_FAILURE);
                        }
                        New_Node->address = address;
                        New_Node->visited = false;
                        New_Node->next = NULL;


                        // *read & write 8 bytes , unsigned long
                        // 下方寫法嚴重錯誤！此時New_Node->replaced_ins仍然沒有被malloc，不能直接dereference它，
                        // 我們只有完成malloc break_point_t* New_Node，所以使用指標需要非常小心
                        // *(New_Node->replaced_ins) = ptrace(PTRACE_PEEKTEXT, child, address, 0);
                        // 正確寫法如下：
                        New_Node->replaced_ins = (unsigned long *)malloc(sizeof(unsigned long));
                        *(New_Node->replaced_ins) = ptrace(PTRACE_PEEKTEXT, child, address, 0);
                        printf("New_Node->replaced_ins: %lx\n", *(New_Node->replaced_ins));
                        unsigned long insert_CC = (*(New_Node->replaced_ins) & 0xFFFFFFFFFFFFFF00) | 0xCC;
                        printf("insert_CC: %lx\n", insert_CC);
                        ptrace(PTRACE_POKETEXT, child, address, insert_CC);


                        // *add to breakpoint list
                        if (break_point_head == NULL)
                        { // first bp
                            break_point_head = New_Node;
                        }
                        else
                        {
                            Insert_bp(New_Node);
                        }
                    } else if (address == regs.rip) {
                        printf("** set a breakpoint at 0x%lx\n", address);

                        break_point_t *New_Node = malloc(sizeof(break_point_t));
                        if (New_Node == NULL)
                        {
                            fprintf(stderr, "Failed to allocate memory\n");
                            exit(EXIT_FAILURE);
                        }
                        New_Node->address = address;
                        New_Node->visited = false;
                        New_Node->next = NULL;


                        New_Node->replaced_ins = (unsigned long *)malloc(sizeof(unsigned long));
                        *(New_Node->replaced_ins) = ptrace(PTRACE_PEEKTEXT, child, address, 0);
                        printf("New_Node->replaced_ins: %lx\n", *(New_Node->replaced_ins));

                        // 需延遲Insert CC
                        // unsigned long insert_CC = (*(New_Node->replaced_ins) & 0xFFFFFFFFFFFFFF00) | 0xCC;
                        // printf("delay insert_CC: %lx\n", insert_CC);
                        // ptrace(PTRACE_POKETEXT, child, address, insert_CC);
                        printf("New_Node->address: %lx\n", New_Node->address);
                        if(restore_CC_after_exec_head == NULL){
                            restore_CC_after_exec_head = create_RCAE(New_Node->address);
                        } else {
                            Insert_RCAE(create_RCAE(New_Node->address));
                        }
                        printf("I still not poke the cc into the breakpoint, just delay.\n");

                        // *add to breakpoint list
                        if (break_point_head == NULL)
                        { // first bp
                            break_point_head = New_Node;
                        }
                        else
                        {
                            Insert_bp(New_Node);
                        }
                    } else {
                        printf("** the breakpoint out of range : 0x%lx, please try again.\n", address);
                    }
                }
                else if (strcmp(user_cmd, cmds[3]) == 0)
                {
                    // method 1
                    ptrace(PTRACE_GETREGS, child, NULL, &anchor_content_self.anchor_regs);
                    
                    char *child_map = malloc(sizeof(char) * 20);
                    sprintf(child_map, "cat /proc/%d/maps", child);
                    system(child_map);
                    sprintf(child_map, "/proc/%d/maps", child);
                    FILE *file = fopen(child_map, "r");
                    if (file == NULL) {
                        printf("Failed to open child_map.\n");
                        exit(EXIT_FAILURE);
                    }


                    char line[256];
                    unsigned long start[100], end[100];
                    int cnt = 0;        //how many writable sections
                    while (fgets(line, sizeof(line), file) != NULL) {
                        char permissions[5];
                        sscanf(line, "%*s %4s", permissions);

                        if (permissions[1] == 'w') {
                            // printf("Writable section found: %s", line);
                            // printf("permissions:%s\n", permissions);
                            if (sscanf(line, "%lx-%lx ", &start[cnt], &end[cnt]) != 2){
                                fprintf(stderr, "Error: Can't find &start/&end ");
                                exit(EXIT_FAILURE);
                            }
                            printf("&start[cnt], &end[cnt]:%lx-%lx\n", start[cnt], end[cnt]);
                            cnt++;
                        }
                    }
                    fclose(file);
                    anchor_content_self.cnt = cnt;
                    anchor_content_self.anchor_memory = (unsigned long**)malloc(sizeof(unsigned long *) * anchor_content_self.cnt);
                    anchor_content_self.start = malloc(sizeof(unsigned long) * anchor_content_self.cnt);
                    anchor_content_self.end = malloc(sizeof(unsigned long) * anchor_content_self.cnt);

                    for (int i = 0; i < anchor_content_self.cnt; i++) {
                        anchor_content_self.start[i] = start[i];
                        anchor_content_self.end[i] = end[i];

                        anchor_content_self.anchor_memory[i] = (unsigned long*)malloc((anchor_content_self.end[i] -anchor_content_self.start[i]));
                        printf("anchor_memory_sec[%d]'s size:%lx\n", i, (anchor_content_self.end[i] -anchor_content_self.start[i]));                

                        int len;
                        if ((anchor_content_self.end[i] -anchor_content_self.start[i])/8 != 0)
                            len = (anchor_content_self.end[i] -anchor_content_self.start[i])/8 + 1;
                        else 
                            len = (anchor_content_self.end[i] -anchor_content_self.start[i])/8;
                        for (int j = 0; j < len; j++) {
                            // printf("j:%d\n", j);
                            // printf("start[i] + j*8:%lx\n", start[i] + j*8);
                            
                            anchor_content_self.anchor_memory[i][j] = ptrace(PTRACE_PEEKDATA, child, start[i] + j*8, 0);
                        }
                        
                    }

                    anchor_content_self.used_flag = true;
                    printf("** dropped an anchor\n");

                    // int fd = open(child_map, O_RDONLY);
                    // if (fd == -1)
                    // {
                    //     perror("open");
                    //     exit(EXIT_FAILURE);
                    // }
                    // char *map = malloc(sizeof(char) * 1000);
                    // int len;
                    // if ((len = read(fp_maps, map, sizeof(map) - 1)) < 0){
                    //     fprintf(stderr, "Error: Can't read child_map");
                    //     exit(1);
                    // }
                    // map[len] = '0';

                    // char *saveptr,*token = strtok_r(map, "\n\r", &saveptr);  //先拿出第一行
                    // char *start, *end;
                    // // 從 buf 字符陣列中讀取每一行，直到讀到 NULL 為止
                    // while ((token = strtok_r(NULL, "\n\r", &saveptr)) != NULL)
                    // {
                    //     if (strstr(token, " rwxp ") == NULL || strstr(token, " rw-p ") == NULL ) // 下一個找到的 r--p 段應該是第三行
                    //         continue;
                    //     else {
                    //         if (sscanf(token, "%lx-%lx ", &start, &end) != 2){
                    //             fprintf(stderr, "Error: Can't find &start/&end ");
                    //             exit(1);
                    //         }
                    //     }
                    // }
                    // close(fd);

                    

                    // unsigned long *anchor_content = malloc(sizeof(unsigned long) * 2);
                    // anchor_content[0] = ptrace(PTRACE_PEEKTEXT, child, (unsigned long)regs.rip, NULL);
                    // anchor_content[1] = ptrace(PTRACE_PEEKTEXT, child, (unsigned long)regs.rip + 8, NULL);
                    // // shellcode:fork()+CC, CC80 CDDB3100000002B8
                    // unsigned long shellcode0 = strtol("0xCC80CDDB3100000002B8", NULL, 16);
                    // unsigned long shellcode1 = strtol("0xCC80", NULL, 16);
                    // ptrace(PTRACE_POKETEXT, child, (unsigned long)regs.rip, shellcode0);
                    // ptrace(PTRACE_POKETEXT, child, (unsigned long)regs.rip + 8, anchor_content[1] & 0xFFFFFFFFFFFF0000 | shellcode1);
                    // ptrace(PTRACE_CONT, child, NULL, NULL);
                    // waitpid(child, &status, 0);
                }
                else if (strcmp(user_cmd, cmds[4]) == 0)
                {
                    if (anchor_content_self.used_flag == false)
                    {
                        printf("** no anchor dropped\n");
                    } else {
                        break_point_t *the_head = break_point_head;
                        while (the_head) {
                            // unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, break_point_head->address, 0);
                            // printf("now_the_ins: %lx\n", now_the_ins);
                            // recover_ins
                            printf("recover_ins: %lx\n", *(the_head->replaced_ins) & (0xFFFFFFFFFFFFFF00) | 0xCC);
                            printf("the_head->address: %lx\n", the_head->address);
                            ptrace(PTRACE_POKETEXT, child, the_head->address, *(the_head->replaced_ins) & (0xFFFFFFFFFFFFFF00) | 0xCC);
                            the_head = the_head->next;
                        }
                        // while (restore_CC_after_exec_head) {
                        //     printf("restore_CC_after_exec_head begin\n");
                        //     unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, restore_CC_after_exec_head->RCAE_address, 0);
                        //     printf("now_the_ins: %lx\n", now_the_ins);
                        //     // recover_ins
                        //     printf("restore_CC_after_exec_head end: %lx\n", (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);
                        //     ptrace(PTRACE_POKETEXT, child, restore_CC_after_exec_head, (now_the_ins & (0xFFFFFFFFFFFFFF00)) | 0xCC);

                        //     RCAE_content *current = restore_CC_after_exec_head;
                        //     restore_CC_after_exec_head = restore_CC_after_exec_head->next;
                        //     free(current);
                        // }

                        printf("** go back to the anchor point\n");
                        
                        printf("RIP: 0x%llx\n", anchor_content_self.anchor_regs.rip);
                        long _offset = ( long)anchor_content_self.anchor_regs.rip - ( long)Child_entryPoint;
                        printf("offset: 0x%lx\n", _offset);
                        // unsigned long _cal_address = (unsigned long)text_sec_data + _offset;
                        long _cal_address = ( long)text_sec + _offset;
                        printf("cal_address: 0x%lx\n", _cal_address);

                        if (_cal_address < ( long)text_sec || _cal_address > ( long)text_sec + text_sec_size)
                        {
                            // printf("** the address is out of the range of the text section.\n");
                            unsigned long* get_five_row;
                            get_five_row = malloc(sizeof(unsigned long) * 5);
                            for(int i=0;i<5;i++){
                                get_five_row[i] = ptrace(PTRACE_PEEKTEXT, child, anchor_content_self.anchor_regs.rip + i * 8, NULL);
                                break_point_t *visited_Node = NULL;
                                if ((visited_Node = Visit_specific_bp(anchor_content_self.anchor_regs.rip + i*8)) != NULL) // stop due to int3(CC)
                                {
                                    get_five_row[i] = *(visited_Node->replaced_ins);
                                }
                                printf("get_five_row[%d]: %lx\n", i, get_five_row[i]);
                                // // 判斷get_five_row裡有沒有CC 要找出換成原本的指令
                                // char* offset = strstr(get_five_row[i], "CC");
                                // if(offset != NULL){
                                //     printf("offset: %s\n", offset);
                                // }
                                // get_five_row[i] = 

                            }
                            // break_point_t *visited_Node = NULL;
                            // if ((visited_Node = Visit_specific_bp(regs.rip + i)) != NULL) // stop due to int3(CC)
                            // {
                            

                            //     // * find the CC in the unsigned long's tail
                            //     printf("recover_ins: %lx\n", (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            //     ptrace(PTRACE_POKETEXT, child, regs.rip, (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            //     // ptrace(PTRACE_POKETEXT, child, regs.rip, *(visited_Node->replaced_ins));
                            // }  
                            printf("here1\n");
                            disassembleInstructions((void *)get_five_row, disassemble_Ins_cnt, (unsigned long)anchor_content_self.anchor_regs.rip, parsing_code_size);
                            printf("here2\n");
                        } else {
                            // *Disassemble instructions starting from the current program counter (RIP)
                            // *改peektext child process .text的內容，而非從elf拿
                            disassembleInstructions((void *)_cal_address, disassemble_Ins_cnt, (unsigned long)anchor_content_self.anchor_regs.rip, parsing_code_size);
                        }
                        // // *Disassemble instructions starting from the current program counter (RIP)
                        // disassembleInstructions((void *)_cal_address, disassemble_Ins_cnt, (unsigned long)anchor_content_self.anchor_regs.rip, parsing_code_size);
                    


                        // time_travel_flag = true;

                        // 單獨處理time travel的bp要延遲補上cc
                        break_point_t *visited_Node = NULL;
                        if ((visited_Node = Visit_specific_bp(anchor_content_self.anchor_regs.rip)) != NULL){
                            // stop due to int3(CC) 且 bp設在第一行程式一開始的地方
                            printf("** there was a bp at 0x%llx.\n", anchor_content_self.anchor_regs.rip);
                            unsigned long now_the_ins = ptrace(PTRACE_PEEKTEXT, child, anchor_content_self.anchor_regs.rip, 0);
                            printf("now_the_ins: %lx\n", now_the_ins);
                            // recover_ins
                            printf("recover_ins: %lx\n", *(visited_Node->replaced_ins));

                            // * find the CC in the unsigned long's tail
                            ptrace(PTRACE_POKETEXT, child, anchor_content_self.anchor_regs.rip, (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            printf("(now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF): %lx\n", (now_the_ins & 0xFFFFFFFFFFFFFF00) | (*(visited_Node->replaced_ins) & 0xFF));
                            // ptrace(PTRACE_POKETEXT, child, anchor_content_self.anchor_regs.rip, *(visited_Node->replaced_ins));

                            

                            if(restore_CC_after_exec_head == NULL){
                                restore_CC_after_exec_head = create_RCAE(anchor_content_self.anchor_regs.rip);
                            } else {
                                Insert_RCAE(create_RCAE(anchor_content_self.anchor_regs.rip));
                            }

                            // restore_CC_after_exec = anchor_content_self.anchor_regs.rip;
                            // printf("restore_CC_after_exec: %lx\n", restore_CC_after_exec);
                            
                        }
                        ptrace(PTRACE_SETREGS, child, NULL, &anchor_content_self.anchor_regs);
                        printf("anchor_content_self.anchor_regs.rip: %llx\n", anchor_content_self.anchor_regs.rip);
                    }
                }
                else
                {
                    printf("Invalid option.\n");
                }
            }
        }
    }
    return 0;
}
