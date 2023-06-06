sort_funcptr_t:
    endbr64     #keypoint
    push rbp
    mov rbp, rsp
   
    xor rcx,rcx
    mov ecx, esi
    mov r8, rcx
    dec r8

    xor rbx, rbx 
    for_x:
        for_y:
            xor rax,rax
            xor r9,r9
            mov rax,QWORD PTR [rdi + 8 * rbx]
            mov r9, QWORD PTR [rdi + 8 * rbx + 8]

            cmp rax, r9
            jg c_value
        c_value_back:
            mov QWORD PTR [rdi + (8 * rbx)], rax
            mov QWORD PTR [rdi + (8 * rbx) + 8], r9
            inc rbx
            cmp rbx, r8
            jb  for_y
        xor rbx, rbx
        loop for_x

    mov rsp, rbp
    pop rbp
    ret

c_value:
    mov r10, rax
    mov rax, r9
    mov r9, r10
    jmp c_value_back