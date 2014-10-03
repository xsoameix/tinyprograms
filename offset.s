	.file	"offset.c"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	DWORD PTR [rbp-16], 5  #    a->a
	mov	DWORD PTR [rbp-12], 10 # a  a->b
	lea	rax, [rbp-16]
	mov	QWORD PTR [rbp-8], rax # * b
	mov	rax, QWORD PTR [rbp-8]
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR [rbp-20], eax # c
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
