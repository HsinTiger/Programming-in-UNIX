sort_funcptr_t:
    push rbp
    mov rbp, rsp
    sub rsp, 16

    mov ecx, [rsi]
    dec ecx

    mov rdi, [rdi]

outer_loop:
    xor edx, edx

inner_loop:
    cmp edi, [rdi, rcx, 8]
    jae outer_loop

    mov ebx, edi
    add ebx, 8
    cmp qword [edi], [ebx]
    jle skip_swap
    mov rax, [edi]
    mov qword [edi], [ebx]
    mov qword [ebx], rax
    mov edx, 1
skip_swap:
    add edi, 8
    jmp inner_loop

    cmp edx, 0
    jne outer_loop

done:
    mov [rdi], rdi
    add rsp, 16
    pop rbp
    ret
