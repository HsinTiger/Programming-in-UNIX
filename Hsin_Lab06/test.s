quicksort:
.LFB23:
	endbr64
	cmp	esi, 1
	jle	.L12
	push	r12
	mov	r10, rdi
	mov	r12d, esi
	push	rbp
	push	rbx
.L2:
	mov	eax, r12d
	lea	ecx, -1[r12]
	mov	rbx, r10
	xor	r8d, r8d
	sar	eax
	cdqe
	mov	rdi, QWORD PTR [r10+rax*8]
	movsx	rax, ecx
	.p2align 4,,10
	.p2align 3
.L3:
	mov	r9, QWORD PTR [rbx]
	lea	rsi, [r10+rax*8]
	mov	ebp, r8d
	mov	rdx, QWORD PTR [rsi]
	cmp	r9, rdi
	jl	.L4
	cmp	rdi, rdx
	jge	.L5
	lea	rax, -8[r10+rax*8]
	.p2align 4,,10
	.p2align 3
.L6:
	mov	rsi, rax
	mov	rdx, QWORD PTR [rax]
	sub	rax, 8
	sub	ecx, 1
	cmp	rdx, rdi
	jg	.L6
.L5:
	cmp	ecx, r8d
	jle	.L7
	mov	QWORD PTR [rbx], rdx
	sub	ecx, 1
	mov	QWORD PTR [rsi], r9
	movsx	rax, ecx
.L4:
	add	r8, 1
	add	rbx, 8
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L7:
	mov	esi, ebp
	mov	rdi, r10
	sub	r12d, ebp
	call	quicksort
	cmp	r12d, 1
	jle	.L1
	mov	r10, rbx
	jmp	.L2
.L1:
	pop	rbx
	pop	rbp
	pop	r12
	ret
.L12:
	ret
.LFE23:
	.size	quicksort, .-quicksort
	.section	.rodata.str1.1,"aMS",@progbits,1