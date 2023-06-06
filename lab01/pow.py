#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import base64
import hashlib
import time
from pwn import *

def cal(ops,op1,op2):
    if (ops == '+'):
        res = int(op1) + int(op2);
    elif (ops == '-'):
        res = int(op1) - int(op2);
    elif (ops == '*'):
        res = int(op1) * int(op2);
    elif (ops == '/'):
        res = int(op1) / int(op2);
    elif (ops == '**'):
        res = int(op1) ** int(op2);
    elif (ops == '//'):
        res = int(op1) // int(op2);
    elif (ops == '%'):
        res = int(op1) % int(op2);
    return res

def solve_pow(r):
    prefix = r.recvline().decode().split("'")[1]
    print(time.time(), "solving pow ...")
    solved = b''
    for i in range(1000000000):
        h = hashlib.sha1((prefix + str(i)).encode()).hexdigest()
        if h[:6] == '000000':
            solved = str(i).encode()
            print("solved =", solved)
            break;
    print(time.time(), "done.")
    r.sendlineafter(b'string S: ', base64.b64encode(solved))
   

def solve_algo(r):
    receive = r.recvuntil('='.encode()).decode().split(' ')
    Num = receive[8]
    op1 = receive[29]
    ops = receive[30]
    op2 = receive[31]
    # print(Num,op1,ops,op2,"\n")
    res1 = cal(ops,op1,op2)
    byte_seq = res1.to_bytes((res1.bit_length() + 7) // 8, byteorder='little')
    r.sendline(base64.b64encode(byte_seq))

    for i in range(int(Num)-1) :
        receive_after = r.recvuntil('='.encode()).decode().split(' ')
        op1 = receive_after[4]
        ops = receive_after[5]
        op2 = receive_after[6]
        # print(receive_after,"\n")
        res1 = cal(ops,op1,op2)
        byte_seq = res1.to_bytes((res1.bit_length() + 7) // 8, byteorder='little')
        r.sendline(base64.b64encode(byte_seq))
    # pass

if __name__ == '__main__':
    #r = remote('localhost', 10330);
    r = remote('up23.zoolab.org', 10363)
    solve_pow(r)
    solve_algo(r)
    r.interactive()
    r.close()

# vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :
