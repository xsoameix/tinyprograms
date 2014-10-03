	.file	"va_list.c"
	.intel_syntax noprefix
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-24], 0
	mov	QWORD PTR [rbp-16], 0
	mov	QWORD PTR [rbp-8], 0
	lea	rax, [rbp-24]
	mov	rdx, QWORD PTR [rbp-40]
	mov	rcx, QWORD PTR [rdx]
	mov	QWORD PTR [rax], rcx
	mov	rcx, QWORD PTR [rdx+8]
	mov	QWORD PTR [rax+8], rcx
	mov	rdx, QWORD PTR [rdx+16]
	mov	QWORD PTR [rax+16], rdx
	mov	DWORD PTR [rbp-28], 1
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.globl	bar
	.type	bar, @function
bar:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 104
	mov	QWORD PTR [rbp-168], rsi
	mov	QWORD PTR [rbp-160], rdx
	mov	QWORD PTR [rbp-152], rcx
	mov	QWORD PTR [rbp-144], r8
	mov	QWORD PTR [rbp-136], r9
	test	al, al
	je	.L3
	movaps	XMMWORD PTR [rbp-128], xmm0
	movaps	XMMWORD PTR [rbp-112], xmm1
	movaps	XMMWORD PTR [rbp-96], xmm2
	movaps	XMMWORD PTR [rbp-80], xmm3
	movaps	XMMWORD PTR [rbp-64], xmm4
	movaps	XMMWORD PTR [rbp-48], xmm5
	movaps	XMMWORD PTR [rbp-32], xmm6
	movaps	XMMWORD PTR [rbp-16], xmm7
.L3:
	mov	DWORD PTR [rbp-212], edi
	mov	DWORD PTR [rbp-200], 8
	mov	DWORD PTR [rbp-196], 48
	lea	rax, [rbp+16]
	mov	QWORD PTR [rbp-192], rax
	lea	rax, [rbp-176]
	mov	QWORD PTR [rbp-184], rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	bar, .-bar
	.ident	"GCC: (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
