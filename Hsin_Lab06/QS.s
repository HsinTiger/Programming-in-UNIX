quicksort:
    endbr64
    push   rbp
    mov    rbp,rsp
    sub    rsp,0x30
    mov    QWORD PTR [rbp-0x28],rdi
    mov    DWORD PTR [rbp-0x2c],esi
    cmp    DWORD PTR [rbp-0x2c],0x1
    jle    quicksort+0x14a
    mov    eax,DWORD PTR [rbp-0x2c]
    mov    edx,eax
    shr    edx,0x1f
    add    eax,edx
    sar    eax,1
    cdqe   
    lea    rdx,QWORD PTR [rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x28]
    add    rax,rdx
    mov    rax,QWORD PTR [rax]
    mov    QWORD PTR [rbp-0x10],rax
    mov    DWORD PTR [rbp-0x18],0x0
    mov    eax,DWORD PTR [rbp-0x2c]
    sub    eax,0x1
    mov    DWORD PTR [rbp-0x14],eax
    jmp    quicksort+0x57

    add    DWORD PTR [rbp-0x18],0x1
    mov    eax,DWORD PTR [rbp-0x18]
    cdqe   
    lea    rdx,QWORD PTR [rax*8+0x0]
    mov    rax,QWORD PTR [rbp-0x28]
    add    rax,rdx
    mov    rax,QWORD PTR [rax]

    cmp    QWORD PTR [rbp-0x10],rax
    jg     quicksort+0x53
    jmp    quicksort+0x7a
    sub    DWORD PTR [rbp-0x14],0x1
    mov    eax,DWORD PTR [rbp-0x14]
    cdqe   
    lea    rdx,QWORD PTR [rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x28]
    add    rax,rdx
    mov    rax,QWORD PTR [rax]
    cmp    QWORD PTR [rbp-0x10],rax
    jl     quicksort+0x76
    mov    eax,DWORD PTR [rbp-0x18]
    cmp    eax,DWORD PTR [rbp-0x14]
    jge    quicksort+0x111
    mov    eax,DWORD PTR [rbp-0x18]
    cdqe   
    lea    rdx,QWORD PTR [rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x28]
    add    rax,rdx
    mov    rax,QWORD PTR [rax]
    mov    QWORD PTR [rbp-0x8],rax
    mov    eax,DWORD PTR [rbp-0x14]
    cdqe   
    lea    rdx,QWORD PTR [rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x28]
    add    rax,rdx
    mov    edx,DWORD PTR [rbp-0x18]
    movsxd rdx,edx
    lea    rcx,QWORD PTR [rdx*8+0x0]

    mov    rdx,QWORD PTR [rbp-0x28]
    add    rdx,rcx
    mov    rax,QWORD PTR [rax]
    mov    QWORD PTR [rdx],rax
    mov    eax,DWORD PTR [rbp-0x14]
    cdqe   
    lea    rdx,QWORD PTR [rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x28]
    add    rdx,rax
    mov    rax,QWORD PTR [rbp-0x8]
    mov    QWORD PTR [rdx],rax
    add    DWORD PTR [rbp-0x18],0x1
    sub    DWORD PTR [rbp-0x14],0x1
    jmp    quicksort+0x57
    nop
    mov    edx,DWORD PTR [rbp-0x18]
    mov    rax,QWORD PTR [rbp-0x28]
    mov    esi,edx
    mov    rdi,rax
    call   quicksort
    mov    eax,DWORD PTR [rbp-0x2c]
    sub    eax,DWORD PTR [rbp-0x18]
    mov    edx,DWORD PTR [rbp-0x18]
    movsxd rdx,edx
    lea    rcx,QWORD PTR[rdx*8+0x0]

    mov    rdx,QWORD PTR [rbp-0x28]
    add    rdx,rcx
    mov    esi,eax
    mov    rdi,rdx
    call   quicksort
    jmp    quicksort+0x14b
    nop

    leave  
    ret    