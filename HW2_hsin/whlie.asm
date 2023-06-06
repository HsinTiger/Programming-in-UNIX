
./while:     file format elf64-x86-64


Disassembly of section .interp:

0000000000000318 <.interp>:
 318:	2f                   	(bad)  
 319:	6c                   	ins    BYTE PTR es:[rdi],dx
 31a:	69 62 36 34 2f 6c 64 	imul   esp,DWORD PTR [rdx+0x36],0x646c2f34
 321:	2d 6c 69 6e 75       	sub    eax,0x756e696c
 326:	78 2d                	js     355 <__abi_tag-0x37>
 328:	78 38                	js     362 <__abi_tag-0x2a>
 32a:	36 2d 36 34 2e 73    	ss sub eax,0x732e3436
 330:	6f                   	outs   dx,DWORD PTR ds:[rsi]
 331:	2e 32 00             	cs xor al,BYTE PTR [rax]

Disassembly of section .note.gnu.property:

0000000000000338 <.note.gnu.property>:
 338:	04 00                	add    al,0x0
 33a:	00 00                	add    BYTE PTR [rax],al
 33c:	20 00                	and    BYTE PTR [rax],al
 33e:	00 00                	add    BYTE PTR [rax],al
 340:	05 00 00 00 47       	add    eax,0x47000000
 345:	4e 55                	rex.WRX push rbp
 347:	00 02                	add    BYTE PTR [rdx],al
 349:	00 00                	add    BYTE PTR [rax],al
 34b:	c0 04 00 00          	rol    BYTE PTR [rax+rax*1],0x0
 34f:	00 03                	add    BYTE PTR [rbx],al
 351:	00 00                	add    BYTE PTR [rax],al
 353:	00 00                	add    BYTE PTR [rax],al
 355:	00 00                	add    BYTE PTR [rax],al
 357:	00 02                	add    BYTE PTR [rdx],al
 359:	80 00 c0             	add    BYTE PTR [rax],0xc0
 35c:	04 00                	add    al,0x0
 35e:	00 00                	add    BYTE PTR [rax],al
 360:	01 00                	add    DWORD PTR [rax],eax
 362:	00 00                	add    BYTE PTR [rax],al
 364:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .note.gnu.build-id:

0000000000000368 <.note.gnu.build-id>:
 368:	04 00                	add    al,0x0
 36a:	00 00                	add    BYTE PTR [rax],al
 36c:	14 00                	adc    al,0x0
 36e:	00 00                	add    BYTE PTR [rax],al
 370:	03 00                	add    eax,DWORD PTR [rax]
 372:	00 00                	add    BYTE PTR [rax],al
 374:	47                   	rex.RXB
 375:	4e 55                	rex.WRX push rbp
 377:	00 22                	add    BYTE PTR [rdx],ah
 379:	e3 ed                	jrcxz  368 <__abi_tag-0x24>
 37b:	c5 83 3a             	(bad)
 37e:	6c                   	ins    BYTE PTR es:[rdi],dx
 37f:	11 13                	adc    DWORD PTR [rbx],edx
 381:	bf 88 56 6b e0       	mov    edi,0xe06b5688
 386:	8a 14 7c             	mov    dl,BYTE PTR [rsp+rdi*2]
 389:	e1 71                	loope  3fc <__abi_tag+0x70>
 38b:	4b                   	rex.WXB

Disassembly of section .note.ABI-tag:

000000000000038c <__abi_tag>:
 38c:	04 00                	add    al,0x0
 38e:	00 00                	add    BYTE PTR [rax],al
 390:	10 00                	adc    BYTE PTR [rax],al
 392:	00 00                	add    BYTE PTR [rax],al
 394:	01 00                	add    DWORD PTR [rax],eax
 396:	00 00                	add    BYTE PTR [rax],al
 398:	47                   	rex.RXB
 399:	4e 55                	rex.WRX push rbp
 39b:	00 00                	add    BYTE PTR [rax],al
 39d:	00 00                	add    BYTE PTR [rax],al
 39f:	00 03                	add    BYTE PTR [rbx],al
 3a1:	00 00                	add    BYTE PTR [rax],al
 3a3:	00 02                	add    BYTE PTR [rdx],al
 3a5:	00 00                	add    BYTE PTR [rax],al
 3a7:	00 00                	add    BYTE PTR [rax],al
 3a9:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .gnu.hash:

00000000000003b0 <.gnu.hash>:
 3b0:	02 00                	add    al,BYTE PTR [rax]
 3b2:	00 00                	add    BYTE PTR [rax],al
 3b4:	06                   	(bad)  
 3b5:	00 00                	add    BYTE PTR [rax],al
 3b7:	00 01                	add    BYTE PTR [rcx],al
 3b9:	00 00                	add    BYTE PTR [rax],al
 3bb:	00 06                	add    BYTE PTR [rsi],al
 3bd:	00 00                	add    BYTE PTR [rax],al
 3bf:	00 00                	add    BYTE PTR [rax],al
 3c1:	00 81 00 00 00 00    	add    BYTE PTR [rcx+0x0],al
 3c7:	00 06                	add    BYTE PTR [rsi],al
 3c9:	00 00                	add    BYTE PTR [rax],al
 3cb:	00 00                	add    BYTE PTR [rax],al
 3cd:	00 00                	add    BYTE PTR [rax],al
 3cf:	00 d1                	add    cl,dl
 3d1:	65 ce                	gs (bad) 
 3d3:	6d                   	ins    DWORD PTR es:[rdi],dx

Disassembly of section .dynsym:

00000000000003d8 <.dynsym>:
	...
 3f0:	10 00                	adc    BYTE PTR [rax],al
 3f2:	00 00                	add    BYTE PTR [rax],al
 3f4:	12 00                	adc    al,BYTE PTR [rax]
	...
 406:	00 00                	add    BYTE PTR [rax],al
 408:	4a 00 00             	rex.WX add BYTE PTR [rax],al
 40b:	00 20                	add    BYTE PTR [rax],ah
	...
 41d:	00 00                	add    BYTE PTR [rax],al
 41f:	00 22                	add    BYTE PTR [rdx],ah
 421:	00 00                	add    BYTE PTR [rax],al
 423:	00 12                	add    BYTE PTR [rdx],dl
	...
 435:	00 00                	add    BYTE PTR [rax],al
 437:	00 66 00             	add    BYTE PTR [rsi+0x0],ah
 43a:	00 00                	add    BYTE PTR [rax],al
 43c:	20 00                	and    BYTE PTR [rax],al
	...
 44e:	00 00                	add    BYTE PTR [rax],al
 450:	75 00                	jne    452 <__abi_tag+0xc6>
 452:	00 00                	add    BYTE PTR [rax],al
 454:	20 00                	and    BYTE PTR [rax],al
	...
 466:	00 00                	add    BYTE PTR [rax],al
 468:	01 00                	add    DWORD PTR [rax],eax
 46a:	00 00                	add    BYTE PTR [rax],al
 46c:	22 00                	and    al,BYTE PTR [rax]
	...

Disassembly of section .dynstr:

0000000000000480 <.dynstr>:
 480:	00 5f 5f             	add    BYTE PTR [rdi+0x5f],bl
 483:	63 78 61             	movsxd edi,DWORD PTR [rax+0x61]
 486:	5f                   	pop    rdi
 487:	66 69 6e 61 6c 69    	imul   bp,WORD PTR [rsi+0x61],0x696c
 48d:	7a 65                	jp     4f4 <__abi_tag+0x168>
 48f:	00 5f 5f             	add    BYTE PTR [rdi+0x5f],bl
 492:	6c                   	ins    BYTE PTR es:[rdi],dx
 493:	69 62 63 5f 73 74 61 	imul   esp,DWORD PTR [rdx+0x63],0x6174735f
 49a:	72 74                	jb     510 <__abi_tag+0x184>
 49c:	5f                   	pop    rdi
 49d:	6d                   	ins    DWORD PTR es:[rdi],dx
 49e:	61                   	(bad)  
 49f:	69 6e 00 70 72 69 6e 	imul   ebp,DWORD PTR [rsi+0x0],0x6e697270
 4a6:	74 66                	je     50e <__abi_tag+0x182>
 4a8:	00 6c 69 62          	add    BYTE PTR [rcx+rbp*2+0x62],ch
 4ac:	63 2e                	movsxd ebp,DWORD PTR [rsi]
 4ae:	73 6f                	jae    51f <__abi_tag+0x193>
 4b0:	2e 36 00 47 4c       	cs ss add BYTE PTR [rdi+0x4c],al
 4b5:	49                   	rex.WB
 4b6:	42                   	rex.X
 4b7:	43 5f                	rex.XB pop r15
 4b9:	32 2e                	xor    ch,BYTE PTR [rsi]
 4bb:	32 2e                	xor    ch,BYTE PTR [rsi]
 4bd:	35 00 47 4c 49       	xor    eax,0x494c4700
 4c2:	42                   	rex.X
 4c3:	43 5f                	rex.XB pop r15
 4c5:	32 2e                	xor    ch,BYTE PTR [rsi]
 4c7:	33 34 00             	xor    esi,DWORD PTR [rax+rax*1]
 4ca:	5f                   	pop    rdi
 4cb:	49 54                	rex.WB push r12
 4cd:	4d 5f                	rex.WRB pop r15
 4cf:	64 65 72 65          	fs gs jb 538 <__abi_tag+0x1ac>
 4d3:	67 69 73 74 65 72 54 	imul   esi,DWORD PTR [ebx+0x74],0x4d547265
 4da:	4d 
 4db:	43 6c                	rex.XB ins BYTE PTR es:[rdi],dx
 4dd:	6f                   	outs   dx,DWORD PTR ds:[rsi]
 4de:	6e                   	outs   dx,BYTE PTR ds:[rsi]
 4df:	65 54                	gs push rsp
 4e1:	61                   	(bad)  
 4e2:	62                   	(bad)  
 4e3:	6c                   	ins    BYTE PTR es:[rdi],dx
 4e4:	65 00 5f 5f          	add    BYTE PTR gs:[rdi+0x5f],bl
 4e8:	67 6d                	ins    DWORD PTR es:[edi],dx
 4ea:	6f                   	outs   dx,DWORD PTR ds:[rsi]
 4eb:	6e                   	outs   dx,BYTE PTR ds:[rsi]
 4ec:	5f                   	pop    rdi
 4ed:	73 74                	jae    563 <__abi_tag+0x1d7>
 4ef:	61                   	(bad)  
 4f0:	72 74                	jb     566 <__abi_tag+0x1da>
 4f2:	5f                   	pop    rdi
 4f3:	5f                   	pop    rdi
 4f4:	00 5f 49             	add    BYTE PTR [rdi+0x49],bl
 4f7:	54                   	push   rsp
 4f8:	4d 5f                	rex.WRB pop r15
 4fa:	72 65                	jb     561 <__abi_tag+0x1d5>
 4fc:	67 69 73 74 65 72 54 	imul   esi,DWORD PTR [ebx+0x74],0x4d547265
 503:	4d 
 504:	43 6c                	rex.XB ins BYTE PTR es:[rdi],dx
 506:	6f                   	outs   dx,DWORD PTR ds:[rsi]
 507:	6e                   	outs   dx,BYTE PTR ds:[rsi]
 508:	65 54                	gs push rsp
 50a:	61                   	(bad)  
 50b:	62                   	.byte 0x62
 50c:	6c                   	ins    BYTE PTR es:[rdi],dx
 50d:	65                   	gs
	...

Disassembly of section .gnu.version:

0000000000000510 <.gnu.version>:
 510:	00 00                	add    BYTE PTR [rax],al
 512:	02 00                	add    al,BYTE PTR [rax]
 514:	01 00                	add    DWORD PTR [rax],eax
 516:	03 00                	add    eax,DWORD PTR [rax]
 518:	01 00                	add    DWORD PTR [rax],eax
 51a:	01 00                	add    DWORD PTR [rax],eax
 51c:	03 00                	add    eax,DWORD PTR [rax]

Disassembly of section .gnu.version_r:

0000000000000520 <.gnu.version_r>:
 520:	01 00                	add    DWORD PTR [rax],eax
 522:	02 00                	add    al,BYTE PTR [rax]
 524:	29 00                	sub    DWORD PTR [rax],eax
 526:	00 00                	add    BYTE PTR [rax],al
 528:	10 00                	adc    BYTE PTR [rax],al
 52a:	00 00                	add    BYTE PTR [rax],al
 52c:	00 00                	add    BYTE PTR [rax],al
 52e:	00 00                	add    BYTE PTR [rax],al
 530:	75 1a                	jne    54c <__abi_tag+0x1c0>
 532:	69 09 00 00 03 00    	imul   ecx,DWORD PTR [rcx],0x30000
 538:	33 00                	xor    eax,DWORD PTR [rax]
 53a:	00 00                	add    BYTE PTR [rax],al
 53c:	10 00                	adc    BYTE PTR [rax],al
 53e:	00 00                	add    BYTE PTR [rax],al
 540:	b4 91                	mov    ah,0x91
 542:	96                   	xchg   esi,eax
 543:	06                   	(bad)  
 544:	00 00                	add    BYTE PTR [rax],al
 546:	02 00                	add    al,BYTE PTR [rax]
 548:	3f                   	(bad)  
 549:	00 00                	add    BYTE PTR [rax],al
 54b:	00 00                	add    BYTE PTR [rax],al
 54d:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .rela.dyn:

0000000000000550 <.rela.dyn>:
 550:	b8 3d 00 00 00       	mov    eax,0x3d
 555:	00 00                	add    BYTE PTR [rax],al
 557:	00 08                	add    BYTE PTR [rax],cl
 559:	00 00                	add    BYTE PTR [rax],al
 55b:	00 00                	add    BYTE PTR [rax],al
 55d:	00 00                	add    BYTE PTR [rax],al
 55f:	00 40 11             	add    BYTE PTR [rax+0x11],al
 562:	00 00                	add    BYTE PTR [rax],al
 564:	00 00                	add    BYTE PTR [rax],al
 566:	00 00                	add    BYTE PTR [rax],al
 568:	c0 3d 00 00 00 00 00 	sar    BYTE PTR [rip+0x0],0x0        # 56f <__abi_tag+0x1e3>
 56f:	00 08                	add    BYTE PTR [rax],cl
	...
 579:	11 00                	adc    DWORD PTR [rax],eax
 57b:	00 00                	add    BYTE PTR [rax],al
 57d:	00 00                	add    BYTE PTR [rax],al
 57f:	00 08                	add    BYTE PTR [rax],cl
 581:	40 00 00             	rex add BYTE PTR [rax],al
 584:	00 00                	add    BYTE PTR [rax],al
 586:	00 00                	add    BYTE PTR [rax],al
 588:	08 00                	or     BYTE PTR [rax],al
 58a:	00 00                	add    BYTE PTR [rax],al
 58c:	00 00                	add    BYTE PTR [rax],al
 58e:	00 00                	add    BYTE PTR [rax],al
 590:	08 40 00             	or     BYTE PTR [rax+0x0],al
 593:	00 00                	add    BYTE PTR [rax],al
 595:	00 00                	add    BYTE PTR [rax],al
 597:	00 d8                	add    al,bl
 599:	3f                   	(bad)  
 59a:	00 00                	add    BYTE PTR [rax],al
 59c:	00 00                	add    BYTE PTR [rax],al
 59e:	00 00                	add    BYTE PTR [rax],al
 5a0:	06                   	(bad)  
 5a1:	00 00                	add    BYTE PTR [rax],al
 5a3:	00 01                	add    BYTE PTR [rcx],al
	...
 5ad:	00 00                	add    BYTE PTR [rax],al
 5af:	00 e0                	add    al,ah
 5b1:	3f                   	(bad)  
 5b2:	00 00                	add    BYTE PTR [rax],al
 5b4:	00 00                	add    BYTE PTR [rax],al
 5b6:	00 00                	add    BYTE PTR [rax],al
 5b8:	06                   	(bad)  
 5b9:	00 00                	add    BYTE PTR [rax],al
 5bb:	00 02                	add    BYTE PTR [rdx],al
	...
 5c5:	00 00                	add    BYTE PTR [rax],al
 5c7:	00 e8                	add    al,ch
 5c9:	3f                   	(bad)  
 5ca:	00 00                	add    BYTE PTR [rax],al
 5cc:	00 00                	add    BYTE PTR [rax],al
 5ce:	00 00                	add    BYTE PTR [rax],al
 5d0:	06                   	(bad)  
 5d1:	00 00                	add    BYTE PTR [rax],al
 5d3:	00 04 00             	add    BYTE PTR [rax+rax*1],al
	...
 5de:	00 00                	add    BYTE PTR [rax],al
 5e0:	f0 3f                	lock (bad) 
 5e2:	00 00                	add    BYTE PTR [rax],al
 5e4:	00 00                	add    BYTE PTR [rax],al
 5e6:	00 00                	add    BYTE PTR [rax],al
 5e8:	06                   	(bad)  
 5e9:	00 00                	add    BYTE PTR [rax],al
 5eb:	00 05 00 00 00 00    	add    BYTE PTR [rip+0x0],al        # 5f1 <__abi_tag+0x265>
 5f1:	00 00                	add    BYTE PTR [rax],al
 5f3:	00 00                	add    BYTE PTR [rax],al
 5f5:	00 00                	add    BYTE PTR [rax],al
 5f7:	00 f8                	add    al,bh
 5f9:	3f                   	(bad)  
 5fa:	00 00                	add    BYTE PTR [rax],al
 5fc:	00 00                	add    BYTE PTR [rax],al
 5fe:	00 00                	add    BYTE PTR [rax],al
 600:	06                   	(bad)  
 601:	00 00                	add    BYTE PTR [rax],al
 603:	00 06                	add    BYTE PTR [rsi],al
	...

Disassembly of section .rela.plt:

0000000000000610 <.rela.plt>:
 610:	d0 3f                	sar    BYTE PTR [rdi],1
 612:	00 00                	add    BYTE PTR [rax],al
 614:	00 00                	add    BYTE PTR [rax],al
 616:	00 00                	add    BYTE PTR [rax],al
 618:	07                   	(bad)  
 619:	00 00                	add    BYTE PTR [rax],al
 61b:	00 03                	add    BYTE PTR [rbx],al
	...

Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    rsp,0x8
    1008:	48 8b 05 d9 2f 00 00 	mov    rax,QWORD PTR [rip+0x2fd9]        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   rax,rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   rax
    1016:	48 83 c4 08          	add    rsp,0x8
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	push   QWORD PTR [rip+0x2f9a]        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 9b 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f9b]        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nop    DWORD PTR [rax]
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	f2 ff 25 ad 2f 00 00 	bnd jmp QWORD PTR [rip+0x2fad]        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

Disassembly of section .plt.sec:

0000000000001050 <printf@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 75 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f75]        # 3fd0 <printf@GLIBC_2.2.5>
    105b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

Disassembly of section .text:

0000000000001060 <_start>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	31 ed                	xor    ebp,ebp
    1066:	49 89 d1             	mov    r9,rdx
    1069:	5e                   	pop    rsi
    106a:	48 89 e2             	mov    rdx,rsp
    106d:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    1071:	50                   	push   rax
    1072:	54                   	push   rsp
    1073:	45 31 c0             	xor    r8d,r8d
    1076:	31 c9                	xor    ecx,ecx
    1078:	48 8d 3d ca 00 00 00 	lea    rdi,[rip+0xca]        # 1149 <main>
    107f:	ff 15 53 2f 00 00    	call   QWORD PTR [rip+0x2f53]        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1085:	f4                   	hlt    
    1086:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    108d:	00 00 00 

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 79 2f 00 00 	lea    rdi,[rip+0x2f79]        # 4010 <__TMC_END__>
    1097:	48 8d 05 72 2f 00 00 	lea    rax,[rip+0x2f72]        # 4010 <__TMC_END__>
    109e:	48 39 f8             	cmp    rax,rdi
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
    10a3:	48 8b 05 36 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f36]        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10aa:	48 85 c0             	test   rax,rax
    10ad:	74 09                	je     10b8 <deregister_tm_clones+0x28>
    10af:	ff e0                	jmp    rax
    10b1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10b8:	c3                   	ret    
    10b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

00000000000010c0 <register_tm_clones>:
    10c0:	48 8d 3d 49 2f 00 00 	lea    rdi,[rip+0x2f49]        # 4010 <__TMC_END__>
    10c7:	48 8d 35 42 2f 00 00 	lea    rsi,[rip+0x2f42]        # 4010 <__TMC_END__>
    10ce:	48 29 fe             	sub    rsi,rdi
    10d1:	48 89 f0             	mov    rax,rsi
    10d4:	48 c1 ee 3f          	shr    rsi,0x3f
    10d8:	48 c1 f8 03          	sar    rax,0x3
    10dc:	48 01 c6             	add    rsi,rax
    10df:	48 d1 fe             	sar    rsi,1
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f05]        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10eb:	48 85 c0             	test   rax,rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmp    rax
    10f2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    10f8:	c3                   	ret    
    10f9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001100 <__do_global_dtors_aux>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	80 3d 05 2f 00 00 00 	cmp    BYTE PTR [rip+0x2f05],0x0        # 4010 <__TMC_END__>
    110b:	75 2b                	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	55                   	push   rbp
    110e:	48 83 3d e2 2e 00 00 	cmp    QWORD PTR [rip+0x2ee2],0x0        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1115:	00 
    1116:	48 89 e5             	mov    rbp,rsp
    1119:	74 0c                	je     1127 <__do_global_dtors_aux+0x27>
    111b:	48 8b 3d e6 2e 00 00 	mov    rdi,QWORD PTR [rip+0x2ee6]        # 4008 <__dso_handle>
    1122:	e8 19 ff ff ff       	call   1040 <__cxa_finalize@plt>
    1127:	e8 64 ff ff ff       	call   1090 <deregister_tm_clones>
    112c:	c6 05 dd 2e 00 00 01 	mov    BYTE PTR [rip+0x2edd],0x1        # 4010 <__TMC_END__>
    1133:	5d                   	pop    rbp
    1134:	c3                   	ret    
    1135:	0f 1f 00             	nop    DWORD PTR [rax]
    1138:	c3                   	ret    
    1139:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001140 <frame_dummy>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	e9 77 ff ff ff       	jmp    10c0 <register_tm_clones>

0000000000001149 <main>:
    1149:	f3 0f 1e fa          	endbr64 
    114d:	55                   	push   rbp
    114e:	48 89 e5             	mov    rbp,rsp
    1151:	48 83 ec 20          	sub    rsp,0x20
    1155:	89 7d ec             	mov    DWORD PTR [rbp-0x14],edi
    1158:	48 89 75 e0          	mov    QWORD PTR [rbp-0x20],rsi
    115c:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [rbp-0x4],0x0
    1163:	eb 1d                	jmp    1182 <main+0x39>
    1165:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
    1168:	89 c6                	mov    esi,eax
    116a:	48 8d 05 93 0e 00 00 	lea    rax,[rip+0xe93]        # 2004 <_IO_stdin_used+0x4>
    1171:	48 89 c7             	mov    rdi,rax
    1174:	b8 00 00 00 00       	mov    eax,0x0
    1179:	e8 d2 fe ff ff       	call   1050 <printf@plt>
    117e:	83 45 fc 01          	add    DWORD PTR [rbp-0x4],0x1
    1182:	83 7d fc 09          	cmp    DWORD PTR [rbp-0x4],0x9
    1186:	7e dd                	jle    1165 <main+0x1c>
    1188:	b8 00 00 00 00       	mov    eax,0x0
    118d:	c9                   	leave  
    118e:	c3                   	ret    

Disassembly of section .fini:

0000000000001190 <_fini>:
    1190:	f3 0f 1e fa          	endbr64 
    1194:	48 83 ec 08          	sub    rsp,0x8
    1198:	48 83 c4 08          	add    rsp,0x8
    119c:	c3                   	ret    

Disassembly of section .rodata:

0000000000002000 <_IO_stdin_used>:
    2000:	01 00                	add    DWORD PTR [rax],eax
    2002:	02 00                	add    al,BYTE PTR [rax]
    2004:	25                   	.byte 0x25
    2005:	64 0a 00             	or     al,BYTE PTR fs:[rax]

Disassembly of section .eh_frame_hdr:

0000000000002008 <__GNU_EH_FRAME_HDR>:
    2008:	01 1b                	add    DWORD PTR [rbx],ebx
    200a:	03 3b                	add    edi,DWORD PTR [rbx]
    200c:	34 00                	xor    al,0x0
    200e:	00 00                	add    BYTE PTR [rax],al
    2010:	05 00 00 00 18       	add    eax,0x18000000
    2015:	f0 ff                	lock (bad) 
    2017:	ff 68 00             	jmp    FWORD PTR [rax+0x0]
    201a:	00 00                	add    BYTE PTR [rax],al
    201c:	38 f0                	cmp    al,dh
    201e:	ff                   	(bad)  
    201f:	ff 90 00 00 00 48    	call   QWORD PTR [rax+0x48000000]
    2025:	f0 ff                	lock (bad) 
    2027:	ff a8 00 00 00 58    	jmp    FWORD PTR [rax+0x58000000]
    202d:	f0 ff                	lock (bad) 
    202f:	ff 50 00             	call   QWORD PTR [rax+0x0]
    2032:	00 00                	add    BYTE PTR [rax],al
    2034:	41 f1                	rex.B int1 
    2036:	ff                   	(bad)  
    2037:	ff c0                	inc    eax
    2039:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .eh_frame:

0000000000002040 <__FRAME_END__-0xa8>:
    2040:	14 00                	adc    al,0x0
    2042:	00 00                	add    BYTE PTR [rax],al
    2044:	00 00                	add    BYTE PTR [rax],al
    2046:	00 00                	add    BYTE PTR [rax],al
    2048:	01 7a 52             	add    DWORD PTR [rdx+0x52],edi
    204b:	00 01                	add    BYTE PTR [rcx],al
    204d:	78 10                	js     205f <__GNU_EH_FRAME_HDR+0x57>
    204f:	01 1b                	add    DWORD PTR [rbx],ebx
    2051:	0c 07                	or     al,0x7
    2053:	08 90 01 00 00 14    	or     BYTE PTR [rax+0x14000001],dl
    2059:	00 00                	add    BYTE PTR [rax],al
    205b:	00 1c 00             	add    BYTE PTR [rax+rax*1],bl
    205e:	00 00                	add    BYTE PTR [rax],al
    2060:	00 f0                	add    al,dh
    2062:	ff                   	(bad)  
    2063:	ff 26                	jmp    QWORD PTR [rsi]
    2065:	00 00                	add    BYTE PTR [rax],al
    2067:	00 00                	add    BYTE PTR [rax],al
    2069:	44 07                	rex.R (bad) 
    206b:	10 00                	adc    BYTE PTR [rax],al
    206d:	00 00                	add    BYTE PTR [rax],al
    206f:	00 24 00             	add    BYTE PTR [rax+rax*1],ah
    2072:	00 00                	add    BYTE PTR [rax],al
    2074:	34 00                	xor    al,0x0
    2076:	00 00                	add    BYTE PTR [rax],al
    2078:	a8 ef                	test   al,0xef
    207a:	ff                   	(bad)  
    207b:	ff 20                	jmp    QWORD PTR [rax]
    207d:	00 00                	add    BYTE PTR [rax],al
    207f:	00 00                	add    BYTE PTR [rax],al
    2081:	0e                   	(bad)  
    2082:	10 46 0e             	adc    BYTE PTR [rsi+0xe],al
    2085:	18 4a 0f             	sbb    BYTE PTR [rdx+0xf],cl
    2088:	0b 77 08             	or     esi,DWORD PTR [rdi+0x8]
    208b:	80 00 3f             	add    BYTE PTR [rax],0x3f
    208e:	1a 3a                	sbb    bh,BYTE PTR [rdx]
    2090:	2a 33                	sub    dh,BYTE PTR [rbx]
    2092:	24 22                	and    al,0x22
    2094:	00 00                	add    BYTE PTR [rax],al
    2096:	00 00                	add    BYTE PTR [rax],al
    2098:	14 00                	adc    al,0x0
    209a:	00 00                	add    BYTE PTR [rax],al
    209c:	5c                   	pop    rsp
    209d:	00 00                	add    BYTE PTR [rax],al
    209f:	00 a0 ef ff ff 10    	add    BYTE PTR [rax+0x10ffffef],ah
	...
    20ad:	00 00                	add    BYTE PTR [rax],al
    20af:	00 14 00             	add    BYTE PTR [rax+rax*1],dl
    20b2:	00 00                	add    BYTE PTR [rax],al
    20b4:	74 00                	je     20b6 <__GNU_EH_FRAME_HDR+0xae>
    20b6:	00 00                	add    BYTE PTR [rax],al
    20b8:	98                   	cwde   
    20b9:	ef                   	out    dx,eax
    20ba:	ff                   	(bad)  
    20bb:	ff 10                	call   QWORD PTR [rax]
	...
    20c5:	00 00                	add    BYTE PTR [rax],al
    20c7:	00 1c 00             	add    BYTE PTR [rax+rax*1],bl
    20ca:	00 00                	add    BYTE PTR [rax],al
    20cc:	8c 00                	mov    WORD PTR [rax],es
    20ce:	00 00                	add    BYTE PTR [rax],al
    20d0:	79 f0                	jns    20c2 <__GNU_EH_FRAME_HDR+0xba>
    20d2:	ff                   	(bad)  
    20d3:	ff 46 00             	inc    DWORD PTR [rsi+0x0]
    20d6:	00 00                	add    BYTE PTR [rax],al
    20d8:	00 45 0e             	add    BYTE PTR [rbp+0xe],al
    20db:	10 86 02 43 0d 06    	adc    BYTE PTR [rsi+0x60d4302],al
    20e1:	7d 0c                	jge    20ef <__FRAME_END__+0x7>
    20e3:	07                   	(bad)  
    20e4:	08 00                	or     BYTE PTR [rax],al
	...

00000000000020e8 <__FRAME_END__>:
    20e8:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .init_array:

0000000000003db8 <__frame_dummy_init_array_entry>:
    3db8:	40 11 00             	rex adc DWORD PTR [rax],eax
    3dbb:	00 00                	add    BYTE PTR [rax],al
    3dbd:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .fini_array:

0000000000003dc0 <__do_global_dtors_aux_fini_array_entry>:
    3dc0:	00 11                	add    BYTE PTR [rcx],dl
    3dc2:	00 00                	add    BYTE PTR [rax],al
    3dc4:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .dynamic:

0000000000003dc8 <_DYNAMIC>:
    3dc8:	01 00                	add    DWORD PTR [rax],eax
    3dca:	00 00                	add    BYTE PTR [rax],al
    3dcc:	00 00                	add    BYTE PTR [rax],al
    3dce:	00 00                	add    BYTE PTR [rax],al
    3dd0:	29 00                	sub    DWORD PTR [rax],eax
    3dd2:	00 00                	add    BYTE PTR [rax],al
    3dd4:	00 00                	add    BYTE PTR [rax],al
    3dd6:	00 00                	add    BYTE PTR [rax],al
    3dd8:	0c 00                	or     al,0x0
    3dda:	00 00                	add    BYTE PTR [rax],al
    3ddc:	00 00                	add    BYTE PTR [rax],al
    3dde:	00 00                	add    BYTE PTR [rax],al
    3de0:	00 10                	add    BYTE PTR [rax],dl
    3de2:	00 00                	add    BYTE PTR [rax],al
    3de4:	00 00                	add    BYTE PTR [rax],al
    3de6:	00 00                	add    BYTE PTR [rax],al
    3de8:	0d 00 00 00 00       	or     eax,0x0
    3ded:	00 00                	add    BYTE PTR [rax],al
    3def:	00 90 11 00 00 00    	add    BYTE PTR [rax+0x11],dl
    3df5:	00 00                	add    BYTE PTR [rax],al
    3df7:	00 19                	add    BYTE PTR [rcx],bl
    3df9:	00 00                	add    BYTE PTR [rax],al
    3dfb:	00 00                	add    BYTE PTR [rax],al
    3dfd:	00 00                	add    BYTE PTR [rax],al
    3dff:	00 b8 3d 00 00 00    	add    BYTE PTR [rax+0x3d],bh
    3e05:	00 00                	add    BYTE PTR [rax],al
    3e07:	00 1b                	add    BYTE PTR [rbx],bl
    3e09:	00 00                	add    BYTE PTR [rax],al
    3e0b:	00 00                	add    BYTE PTR [rax],al
    3e0d:	00 00                	add    BYTE PTR [rax],al
    3e0f:	00 08                	add    BYTE PTR [rax],cl
    3e11:	00 00                	add    BYTE PTR [rax],al
    3e13:	00 00                	add    BYTE PTR [rax],al
    3e15:	00 00                	add    BYTE PTR [rax],al
    3e17:	00 1a                	add    BYTE PTR [rdx],bl
    3e19:	00 00                	add    BYTE PTR [rax],al
    3e1b:	00 00                	add    BYTE PTR [rax],al
    3e1d:	00 00                	add    BYTE PTR [rax],al
    3e1f:	00 c0                	add    al,al
    3e21:	3d 00 00 00 00       	cmp    eax,0x0
    3e26:	00 00                	add    BYTE PTR [rax],al
    3e28:	1c 00                	sbb    al,0x0
    3e2a:	00 00                	add    BYTE PTR [rax],al
    3e2c:	00 00                	add    BYTE PTR [rax],al
    3e2e:	00 00                	add    BYTE PTR [rax],al
    3e30:	08 00                	or     BYTE PTR [rax],al
    3e32:	00 00                	add    BYTE PTR [rax],al
    3e34:	00 00                	add    BYTE PTR [rax],al
    3e36:	00 00                	add    BYTE PTR [rax],al
    3e38:	f5                   	cmc    
    3e39:	fe                   	(bad)  
    3e3a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
    3e3d:	00 00                	add    BYTE PTR [rax],al
    3e3f:	00 b0 03 00 00 00    	add    BYTE PTR [rax+0x3],dh
    3e45:	00 00                	add    BYTE PTR [rax],al
    3e47:	00 05 00 00 00 00    	add    BYTE PTR [rip+0x0],al        # 3e4d <_DYNAMIC+0x85>
    3e4d:	00 00                	add    BYTE PTR [rax],al
    3e4f:	00 80 04 00 00 00    	add    BYTE PTR [rax+0x4],al
    3e55:	00 00                	add    BYTE PTR [rax],al
    3e57:	00 06                	add    BYTE PTR [rsi],al
    3e59:	00 00                	add    BYTE PTR [rax],al
    3e5b:	00 00                	add    BYTE PTR [rax],al
    3e5d:	00 00                	add    BYTE PTR [rax],al
    3e5f:	00 d8                	add    al,bl
    3e61:	03 00                	add    eax,DWORD PTR [rax]
    3e63:	00 00                	add    BYTE PTR [rax],al
    3e65:	00 00                	add    BYTE PTR [rax],al
    3e67:	00 0a                	add    BYTE PTR [rdx],cl
    3e69:	00 00                	add    BYTE PTR [rax],al
    3e6b:	00 00                	add    BYTE PTR [rax],al
    3e6d:	00 00                	add    BYTE PTR [rax],al
    3e6f:	00 8f 00 00 00 00    	add    BYTE PTR [rdi+0x0],cl
    3e75:	00 00                	add    BYTE PTR [rax],al
    3e77:	00 0b                	add    BYTE PTR [rbx],cl
    3e79:	00 00                	add    BYTE PTR [rax],al
    3e7b:	00 00                	add    BYTE PTR [rax],al
    3e7d:	00 00                	add    BYTE PTR [rax],al
    3e7f:	00 18                	add    BYTE PTR [rax],bl
    3e81:	00 00                	add    BYTE PTR [rax],al
    3e83:	00 00                	add    BYTE PTR [rax],al
    3e85:	00 00                	add    BYTE PTR [rax],al
    3e87:	00 15 00 00 00 00    	add    BYTE PTR [rip+0x0],dl        # 3e8d <_DYNAMIC+0xc5>
	...
    3e95:	00 00                	add    BYTE PTR [rax],al
    3e97:	00 03                	add    BYTE PTR [rbx],al
    3e99:	00 00                	add    BYTE PTR [rax],al
    3e9b:	00 00                	add    BYTE PTR [rax],al
    3e9d:	00 00                	add    BYTE PTR [rax],al
    3e9f:	00 b8 3f 00 00 00    	add    BYTE PTR [rax+0x3f],bh
    3ea5:	00 00                	add    BYTE PTR [rax],al
    3ea7:	00 02                	add    BYTE PTR [rdx],al
    3ea9:	00 00                	add    BYTE PTR [rax],al
    3eab:	00 00                	add    BYTE PTR [rax],al
    3ead:	00 00                	add    BYTE PTR [rax],al
    3eaf:	00 18                	add    BYTE PTR [rax],bl
    3eb1:	00 00                	add    BYTE PTR [rax],al
    3eb3:	00 00                	add    BYTE PTR [rax],al
    3eb5:	00 00                	add    BYTE PTR [rax],al
    3eb7:	00 14 00             	add    BYTE PTR [rax+rax*1],dl
    3eba:	00 00                	add    BYTE PTR [rax],al
    3ebc:	00 00                	add    BYTE PTR [rax],al
    3ebe:	00 00                	add    BYTE PTR [rax],al
    3ec0:	07                   	(bad)  
    3ec1:	00 00                	add    BYTE PTR [rax],al
    3ec3:	00 00                	add    BYTE PTR [rax],al
    3ec5:	00 00                	add    BYTE PTR [rax],al
    3ec7:	00 17                	add    BYTE PTR [rdi],dl
    3ec9:	00 00                	add    BYTE PTR [rax],al
    3ecb:	00 00                	add    BYTE PTR [rax],al
    3ecd:	00 00                	add    BYTE PTR [rax],al
    3ecf:	00 10                	add    BYTE PTR [rax],dl
    3ed1:	06                   	(bad)  
    3ed2:	00 00                	add    BYTE PTR [rax],al
    3ed4:	00 00                	add    BYTE PTR [rax],al
    3ed6:	00 00                	add    BYTE PTR [rax],al
    3ed8:	07                   	(bad)  
    3ed9:	00 00                	add    BYTE PTR [rax],al
    3edb:	00 00                	add    BYTE PTR [rax],al
    3edd:	00 00                	add    BYTE PTR [rax],al
    3edf:	00 50 05             	add    BYTE PTR [rax+0x5],dl
    3ee2:	00 00                	add    BYTE PTR [rax],al
    3ee4:	00 00                	add    BYTE PTR [rax],al
    3ee6:	00 00                	add    BYTE PTR [rax],al
    3ee8:	08 00                	or     BYTE PTR [rax],al
    3eea:	00 00                	add    BYTE PTR [rax],al
    3eec:	00 00                	add    BYTE PTR [rax],al
    3eee:	00 00                	add    BYTE PTR [rax],al
    3ef0:	c0 00 00             	rol    BYTE PTR [rax],0x0
    3ef3:	00 00                	add    BYTE PTR [rax],al
    3ef5:	00 00                	add    BYTE PTR [rax],al
    3ef7:	00 09                	add    BYTE PTR [rcx],cl
    3ef9:	00 00                	add    BYTE PTR [rax],al
    3efb:	00 00                	add    BYTE PTR [rax],al
    3efd:	00 00                	add    BYTE PTR [rax],al
    3eff:	00 18                	add    BYTE PTR [rax],bl
    3f01:	00 00                	add    BYTE PTR [rax],al
    3f03:	00 00                	add    BYTE PTR [rax],al
    3f05:	00 00                	add    BYTE PTR [rax],al
    3f07:	00 1e                	add    BYTE PTR [rsi],bl
    3f09:	00 00                	add    BYTE PTR [rax],al
    3f0b:	00 00                	add    BYTE PTR [rax],al
    3f0d:	00 00                	add    BYTE PTR [rax],al
    3f0f:	00 08                	add    BYTE PTR [rax],cl
    3f11:	00 00                	add    BYTE PTR [rax],al
    3f13:	00 00                	add    BYTE PTR [rax],al
    3f15:	00 00                	add    BYTE PTR [rax],al
    3f17:	00 fb                	add    bl,bh
    3f19:	ff                   	(bad)  
    3f1a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
    3f1d:	00 00                	add    BYTE PTR [rax],al
    3f1f:	00 01                	add    BYTE PTR [rcx],al
    3f21:	00 00                	add    BYTE PTR [rax],al
    3f23:	08 00                	or     BYTE PTR [rax],al
    3f25:	00 00                	add    BYTE PTR [rax],al
    3f27:	00 fe                	add    dh,bh
    3f29:	ff                   	(bad)  
    3f2a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
    3f2d:	00 00                	add    BYTE PTR [rax],al
    3f2f:	00 20                	add    BYTE PTR [rax],ah
    3f31:	05 00 00 00 00       	add    eax,0x0
    3f36:	00 00                	add    BYTE PTR [rax],al
    3f38:	ff                   	(bad)  
    3f39:	ff                   	(bad)  
    3f3a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
    3f3d:	00 00                	add    BYTE PTR [rax],al
    3f3f:	00 01                	add    BYTE PTR [rcx],al
    3f41:	00 00                	add    BYTE PTR [rax],al
    3f43:	00 00                	add    BYTE PTR [rax],al
    3f45:	00 00                	add    BYTE PTR [rax],al
    3f47:	00 f0                	add    al,dh
    3f49:	ff                   	(bad)  
    3f4a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
    3f4d:	00 00                	add    BYTE PTR [rax],al
    3f4f:	00 10                	add    BYTE PTR [rax],dl
    3f51:	05 00 00 00 00       	add    eax,0x0
    3f56:	00 00                	add    BYTE PTR [rax],al
    3f58:	f9                   	stc    
    3f59:	ff                   	(bad)  
    3f5a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
    3f5d:	00 00                	add    BYTE PTR [rax],al
    3f5f:	00 03                	add    BYTE PTR [rbx],al
	...

Disassembly of section .got:

0000000000003fb8 <_GLOBAL_OFFSET_TABLE_>:
    3fb8:	c8 3d 00 00          	enter  0x3d,0x0
	...
    3fd0:	30 10                	xor    BYTE PTR [rax],dl
	...

Disassembly of section .data:

0000000000004000 <__data_start>:
	...

0000000000004008 <__dso_handle>:
    4008:	08 40 00             	or     BYTE PTR [rax+0x0],al
    400b:	00 00                	add    BYTE PTR [rax],al
    400d:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .bss:

0000000000004010 <completed.0>:
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	47                   	rex.RXB
   1:	43                   	rex.XB
   2:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   5:	28 55 62             	sub    BYTE PTR [rbp+0x62],dl
   8:	75 6e                	jne    78 <__abi_tag-0x314>
   a:	74 75                	je     81 <__abi_tag-0x30b>
   c:	20 31                	and    BYTE PTR [rcx],dh
   e:	31 2e                	xor    DWORD PTR [rsi],ebp
  10:	33 2e                	xor    ebp,DWORD PTR [rsi]
  12:	30 2d 31 75 62 75    	xor    BYTE PTR [rip+0x75627531],ch        # 75627549 <_end+0x75623531>
  18:	6e                   	outs   dx,BYTE PTR ds:[rsi]
  19:	74 75                	je     90 <__abi_tag-0x2fc>
  1b:	31 7e 32             	xor    DWORD PTR [rsi+0x32],edi
  1e:	32 2e                	xor    ch,BYTE PTR [rsi]
  20:	30 34 2e             	xor    BYTE PTR [rsi+rbp*1],dh
  23:	31 29                	xor    DWORD PTR [rcx],ebp
  25:	20 31                	and    BYTE PTR [rcx],dh
  27:	31 2e                	xor    DWORD PTR [rsi],ebp
  29:	33 2e                	xor    ebp,DWORD PTR [rsi]
  2b:	30 00                	xor    BYTE PTR [rax],al
