sort_funcptr_t:
    push rbp
    mov rbp, rsp
    sub rsp, 16        

    mov QWORD PTR [rbp-8], rdi   #save rdi (first parameter, long *numbers) to stack at rbp-8
    mov QWORD PTR [rbp-16], rsi  #save rsi (second parameter, int n) to stack at rbp-16  

    mov rcx, rsi    
    dec rcx           

    imul rcx, rcx, 8            #lea rdx, [rdi + rcx*8] 
    mov rdx, rdi
    add rdx, rcx

outer_loop:
    mov rcx, QWORD PTR [rbp-8]
    xor edx, edx         

inner_loop:
    mov rbx, rcx
    add rbx, 8           
    mov rax, QWORD PTR [rcx]
    cmp rax, QWORD PTR [rbx]
    jge skip_swap

    xchg rax, QWORD PTR [rbx]
    mov QWORD PTR [rcx], rax
    add edx, 1     

skip_swap:
    add rcx, 8           
    cmp rcx, rdx
    jb inner_loop        

    cmp edx, 0           
    jne outer_loop       
done:
    add rsp, 16          
    pop rbp
    ret 
