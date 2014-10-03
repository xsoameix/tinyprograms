	.intel_syntax noprefix
	.text
	.globl	_start
_start:
	push	rbp
	mov	rbp, rsp
	and	rsp, -8
	sub	rsp, 16
	fldz
	mov	QWORD PTR [rsp], 0x6100
	mov	rbx, QWORD PTR .LC0
	mov	QWORD PTR [rsp+8], rbx
	fcom	QWORD PTR [rsp+8]
	fstsw	ax
    test ah,0x41
    jnz .L2
.L5:
	mov	rax, 1
	mov	rdi, 1
	lea	rsi, QWORD PTR [rsp]
	mov	rdx, 2
	syscall
.L2:
	mov	rax, 60
	mov	rdi, 0
	syscall
.LFE0:
	.section	.rodata
	.align 8
.LC0:
	.long	0x00000000
	.long	0xbff00000
