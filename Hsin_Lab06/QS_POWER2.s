quicksort:
    endbr64 
    lea    r8d,[rsi-0x1]
    push   rbp
    push   r12
    mov    r9,rdi
    mov    r12d,esi
    mov    edx,r8d
    push   rbx
    cmp    esi,0xf
    jle    quicksort+0xeb
    mov    eax,r12d
    xor    ebp,ebp
    sar    eax,1
    cdqe   
    mov    rsi,QWORD PTR [r9+rax*8]
    nop    DWORD PTR [rax+rax*1+0x0]
    movsxd rax,ebp
    shl    rax,0x3
    lea    rbx,[r9+rax*1]
    cmp    ebp,edx
    jg     quicksort+0xb1
    movsxd r10,edx
    mov    rcx,QWORD PTR [rbx]
    lea    rax,[r9+rax*1+0x8]
    lea    r8,[r9+r10*8]
    mov    rdi,QWORD PTR [r8]
    cmp    rsi,rcx
    jle    quicksort+0xd8
    nop    WORD PTR [rax+rax*1+0x0]
    mov    rbx,rax
    mov    rcx,QWORD PTR [rax]
    lea    rax,[rax+0x8]
    add    ebp,0x1
    cmp    rcx,rsi
    jl     quicksort+0x60
    cmp    rsi,rdi
    jge    quicksort+0x92
    lea    rax,[r9+r10*8-0x8]
    nop    DWORD PTR [rax+0x0]
    mov    r8,rax
    mov    rdi,QWORD PTR [rax]
    sub    rax,0x8
    sub    edx,0x1
    cmp    rdi,rsi
    jg     quicksort+0x80
    cmp    ebp,edx
    jg     quicksort+0x30
    mov    QWORD PTR [rbx],rdi
    add    ebp,0x1
    sub    edx,0x1
    mov    QWORD PTR [r8],rcx
    movsxd rax,ebp
    shl    rax,0x3
    lea    rbx,[r9+rax*1]
    cmp    ebp,edx
    jle    quicksort+0x3f
    lea    esi,[rdx+0x1]
    mov    rdi,r9
    sub    r12d,ebp
    call   quicksort
    lea    r8d,[r12-0x1]
    mov    edx,r8d
    cmp    r12d,0xf
    jle    quicksort+0xee
    mov    r9,rbx
    jmp    quicksort+0x1e
    nop    DWORD PTR [rax]
    cmp    rsi,rdi
    jl     quicksort+0x77
    mov    QWORD PTR [rbx],rdi
    add    ebp,0x1
    sub    edx,0x1
    mov    QWORD PTR [r8],rcx
    jmp    quicksort+0xa2
    mov    rbx,rdi
    xor    edi,edi
    cmp    r12d,0x1
    jle    quicksort+0x136
    cs nop WORD PTR [rax+rax*1+0x0]

    mov    rsi,QWORD PTR [rbx+rdi*8+0x8]
    mov    rax,rdi
    nop    DWORD PTR [rax+rax*1+0x0]

    mov    rdx,QWORD PTR [rbx+rax*8]
    cmp    rdx,rsi
    jle    quicksort+0x13b
    mov    QWORD PTR [rbx+rax*8+0x8],rdx
    sub    rax,0x1
    cmp    eax,0xffffffff
    jne    quicksort+0x110
    mov    rax,rbx
    add    rdi,0x1
    mov    QWORD PTR [rax],rsi
    cmp    r8,rdi
    jne    quicksort+0x100
    pop    rbx
    pop    r12
    pop    rbp

    ret    
    lea    eax,[rax+0x1]
    cdqe   
    lea    rax,[rbx+rax*8]
    jmp    quicksort+0x12a
