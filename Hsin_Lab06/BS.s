bubble_sort:
    endbr64 
    push   rbp
    mov    rbp,rsp
    mov    QWORD PTR [rbp-0x18],rdi
    mov    DWORD PTR [rbp-0x1c],esi
    mov    DWORD PTR [rbp-0x10],0x0
    jmp    bubble_sort+0xe5
    mov    DWORD PTR [rbp-0xc],0x0
    jmp    bubble_sort+0xcf
    mov    eax,DWORD PTR [rbp-0xc]
    cdqe   
    lea    rdx,[rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x18]
    add    rax,rdx
    mov    rdx,QWORD PTR [rax]
    mov    eax,DWORD PTR [rbp-0xc]
    cdqe   
    add    rax,0x1
    lea    rcx,[rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x18]
    add    rax,rcx
    mov    rax,QWORD PTR [rax]
    cmp    rdx,rax
    jle    bubble_sort+0xcb
    mov    eax,DWORD PTR [rbp-0xc]
    cdqe   
    lea    rdx,[rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x18]
    add    rax,rdx
    mov    rax,QWORD PTR [rax]
    mov    QWORD PTR [rbp-0x8],rax
    mov    eax,DWORD PTR [rbp-0xc]
    cdqe   
    add    rax,0x1
    lea    rdx,[rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x18]
    add    rax,rdx
    mov    edx,DWORD PTR [rbp-0xc]
    movsxd rdx,edx
    lea    rcx,[rdx*8+0x0]

    mov    rdx,QWORD PTR [rbp-0x18]
    add    rdx,rcx
    mov    rax,QWORD PTR [rax]
    mov    QWORD PTR [rdx],rax
    mov    eax,DWORD PTR [rbp-0xc]
    cdqe   
    add    rax,0x1
    lea    rdx,[rax*8+0x0]

    mov    rax,QWORD PTR [rbp-0x18]
    add    rdx,rax
    mov    rax,QWORD PTR [rbp-0x8]
    mov    QWORD PTR [rdx],rax
    add    DWORD PTR [rbp-0xc],0x1
    mov    eax,DWORD PTR [rbp-0x1c]
    sub    eax,DWORD PTR [rbp-0x10]
    sub    eax,0x1
    cmp    DWORD PTR [rbp-0xc],eax
    jl     bubble_sort+0x27
    add    DWORD PTR [rbp-0x10],0x1
    mov    eax,DWORD PTR [rbp-0x1c]
    sub    eax,0x1
    cmp    DWORD PTR [rbp-0x10],eax
    jl     bubble_sort+0x1b
    nop
    nop
    pop    rbp
    ret    