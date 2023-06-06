quicksort:
.LFB5512:
	endbr64
	lea	r8d, -1[rsi]
	push	r12
	mov	r9, rdi
	mov	r12d, esi
	push	rbp
	mov	edx, r8d
	push	rbx
	cmp	esi, 15
	jle	.L32
.L2:
	mov	eax, r12d
	xor	ebp, ebp
	sar	eax
	cdqe
	mov	rsi, QWORD PTR [r9+rax*8]
	.p2align 4,,10
	.p2align 3
.L13:
	movsx	rax, ebp
	sal	rax, 3
	lea	rbx, [r9+rax]
	cmp	ebp, edx
	jg	.L14
.L34:
	movsx	r10, edx
	mov	rcx, QWORD PTR [rbx]
	lea	rax, 8[r9+rax]
	lea	r8, [r9+r10*8]
	mov	rdi, QWORD PTR [r8]
	cmp	rsi, rcx
	jle	.L33
	.p2align 4,,10
	.p2align 3
.L10:
	mov	rbx, rax
	mov	rcx, QWORD PTR [rax]
	lea	rax, 8[rax]
	add	ebp, 1
	cmp	rcx, rsi
	jl	.L10
	cmp	rsi, rdi
	jge	.L11
.L18:
	lea	rax, -8[r9+r10*8]
	.p2align 4,,10
	.p2align 3
.L12:
	mov	r8, rax
	mov	rdi, QWORD PTR [rax]
	sub	rax, 8
	sub	edx, 1
	cmp	rdi, rsi
	jg	.L12
.L11:
	cmp	ebp, edx
	jg	.L13
	mov	QWORD PTR [rbx], rdi
	add	ebp, 1
	sub	edx, 1
	mov	QWORD PTR [r8], rcx
.L35:
	movsx	rax, ebp
	sal	rax, 3
	lea	rbx, [r9+rax]
	cmp	ebp, edx
	jle	.L34
.L14:
	lea	esi, 1[rdx]
	mov	rdi, r9
	sub	r12d, ebp
	call	quicksort
	lea	r8d, -1[r12]
	mov	edx, r8d
	cmp	r12d, 15
	jle	.L17
	mov	r9, rbx
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L33:
	cmp	rsi, rdi
	jl	.L18
	mov	QWORD PTR [rbx], rdi
	add	ebp, 1
	sub	edx, 1
	mov	QWORD PTR [r8], rcx
	jmp	.L35
.L32:
	mov	rbx, rdi
.L17:
	xor	edi, edi
	cmp	r12d, 1
	jle	.L1
	.p2align 4,,10
	.p2align 3
.L7:
	mov	rsi, QWORD PTR 8[rbx+rdi*8]
	mov	rax, rdi
	.p2align 4,,10
	.p2align 3
.L4:
	mov	rdx, QWORD PTR [rbx+rax*8]
	cmp	rdx, rsi
	jle	.L36
	mov	QWORD PTR 8[rbx+rax*8], rdx
	sub	rax, 1
	cmp	eax, -1
	jne	.L4
	mov	rax, rbx
.L5:
	add	rdi, 1
	mov	QWORD PTR [rax], rsi
	cmp	r8, rdi
	jne	.L7
.L1:
	pop	rbx
	pop	rbp
	pop	r12
	ret
.L36:
	lea	eax, 1[rax]
	cdqe
	lea	rax, [rbx+rax*8]
	jmp	.L5
.LFE5512:
	.size	quicksort, .-quicksort
	.section	.rodata.str1.1,"aMS",@progbits,1
