sort_funcptr_t:
    push rbp
    mov rbp, rsp
    sub rsp, 16        

    mov QWORD PTR [rbp-8], rdi   #save rdi (first parameter, long *numbers) to stack at rbp-8
    mov DWORD PTR [rbp-16], esi  #save esi (second parameter, int n) to stack at rbp-16  

    xor rax, rax         
    mov eax, DWORD PTR [rbp-16]   
    cdqe
    dec rax          
    imul rax, rax, 8

    xor rdx, rdx    
    mov rdx, QWORD PTR [rbp-8]
    add rdx, rax

outer_loop:
    mov rcx, QWORD PTR [rbp-8]
    xor r8, r8         

inner_loop:
    mov rbx, rcx
    add rbx, 8           
    mov rax, QWORD PTR [rcx]
    cmp rax, QWORD PTR [rbx]
    jle skip_swap

    xchg rax, QWORD PTR [rbx]
    mov QWORD PTR [rcx], rax
    add r8, 1     

skip_swap:
    add rcx, 8           
    cmp rcx, rdx
    jl inner_loop        

    cmp r8, 0           
    jnz outer_loop       
done:
    add rsp, 16          
    pop rbp
    ret 
