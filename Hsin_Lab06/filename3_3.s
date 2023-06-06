sort_funcptr_t:
    push rbp
    mov rbp, rsp
   
    xor rcx, rcx
    mov ecx, esi
    mov r8, rcx
    dec r8

    xor rbx, rbx 
for_x:
    for_y:
        mov rax, QWORD PTR [rdi + 8 * rbx]
        mov r9, QWORD PTR [rdi + 8 * rbx + 8]
        mov r10, rax
        mov r11, r9
        shr r10, 63 #將最高位移至最低位
        shr r11, 63 #將最高位移至最低位
        xor rax, r10 #無號比較操作
        xor r9, r11 #無號比較操作
        cmp rax, r9 #比較操作
        cmova r10, rax
        cmova rax, r9
        cmova r9, r10
        mov QWORD PTR [rdi + (8 * rbx)], rax
        mov QWORD PTR [rdi + (8 * rbx) + 8], r9
        inc rbx
        cmp rbx, r8
        jb for_y
    xor rbx, rbx
    loop for_x

    mov rsp, rbp
    pop rbp
    ret
