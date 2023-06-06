quicksort: 
    endbr64 
    cmp    esi,0x1
    jle    quicksort+0xa0
    push   r12
    mov    r10,rdi
    mov    r12d,esi
    push   rbp
    push   rbx
    mov    eax,r12d
    lea    ecx,[r12-0x1]
    mov    rbx,r10
    xor    r8d,r8d
    sar    eax,1
    cdqe   
    mov    rdi,QWORD PTR [r10+rax*8]
    movsxd rax,ecx
    mov    r9,QWORD PTR [rbx]
    lea    rsi,[r10+rax*8]
    mov    ebp,r8d
    mov    rdx,QWORD PTR [rsi]
    cmp    r9,rdi
    jl     quicksort+0x73
    cmp    rdi,rdx
    jge    quicksort+0x62
    lea    rax,[r10+rax*8-0x8]
    nop    DWORD PTR [rax+0x0]
    mov    rsi,rax
    mov    rdx,QWORD PTR [rax]
    sub    rax,0x8
    sub    ecx,0x1
    cmp    rdx,rdi
    jg     quicksort+0x50
    cmp    ecx,r8d
    jle    quicksort+0x80
    mov    QWORD PTR [rbx],rdx
    sub    ecx,0x1
    mov    QWORD PTR [rsi],r9
    movsxd rax,ecx
    add    r8,0x1
    add    rbx,0x8
    jmp    quicksort+0x30
    nop    DWORD PTR [rax]
    mov    esi,ebp
    mov    rdi,r10
    sub    r12d,ebp
    call   quicksort
    cmp    r12d,0x1
    jle    quicksort+0x9b
    mov    r10,rbx
    jmp    quicksort+0x17
    pop    rbx
    pop    rbp
    pop    r12
    ret    
    ret    