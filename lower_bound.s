	.file	"lower_bound.c"
	.section	.rodata
.LC0:
	.string	"d%d "
	.text
	.globl	lower_bound
	.type	lower_bound, @function
lower_bound:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	sarl	-28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -8(%rbp)
	jmp	.L2
.L4:
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	%eax, -4(%rbp)
	sarl	-28(%rbp)
	movl	-32(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jg	.L3
	movl	-28(%rbp), %eax
	notl	%eax
	addl	%eax, -8(%rbp)
	jmp	.L2
.L3:
	movl	-28(%rbp), %eax
	addl	$1, %eax
	addl	%eax, -8(%rbp)
.L2:
	cmpl	$0, -28(%rbp)
	je	.L4
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	lower_bound, .-lower_bound
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	$1, -48(%rbp)
	movq	$2, -40(%rbp)
	movq	$2, -32(%rbp)
	movq	$3, -24(%rbp)
	movq	$3, -16(%rbp)
	movq	$4, -8(%rbp)
	leaq	-48(%rbp), %rax
	movl	$2, %edx
	movl	$6, %esi
	movq	%rax, %rdi
	call	lower_bound
	leaq	-48(%rbp), %rax
	movl	$3, %edx
	movl	$6, %esi
	movq	%rax, %rdi
	call	lower_bound
	leaq	-48(%rbp), %rax
	movl	$4, %edx
	movl	$6, %esi
	movq	%rax, %rdi
	call	lower_bound
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
