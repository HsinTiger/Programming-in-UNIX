# test1.py
from capstone import *
from pwn import *

CODE = b"\x55\x48\x8b\x05\xb8\x13\x00\x00\x58\xc3\x5f\xc3\x0f\x05\xc3\x00"
CODE2 = p32(12783365)
print(0xc30f05)

md = Cs(CS_ARCH_X86, CS_MODE_64)
for i in md.disasm(CODE2, 0x1000):
    print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
