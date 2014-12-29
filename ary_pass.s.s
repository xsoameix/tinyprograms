	.file	"ary_pass.c"
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	-8(%rbp), %rdx
	addq	$8, %rdx
	movq	(%rdx), %rdx
	addq	$2, %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$16, %rax
	movq	-8(%rbp), %rdx
	addq	$16, %rdx
	movq	(%rdx), %rdx
	addq	$3, %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$24, %rax
	movq	-8(%rbp), %rdx
	addq	$24, %rdx
	movq	(%rdx), %rdx
	addq	$4, %rdx
	movq	%rdx, (%rax)

	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	-8(%rbp), %rdx
	addq	$32, %rdx
	movq	(%rdx), %rdx
	addq	$5, %rdx
	movq	%rdx, (%rax)

	movq	-8(%rbp), %rax
	addq	$40, %rax
	movq	-8(%rbp), %rdx
	addq	$40, %rdx
	movq	(%rdx), %rdx
	addq	$6, %rdx
	movq	%rdx, (%rax)

	movq	-8(%rbp), %rax
	addq	$48, %rax
	movq	-8(%rbp), %rdx
	addq	$48, %rdx
	movq	(%rdx), %rdx
	addq	$7, %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$56, %rax
	movq	-8(%rbp), %rdx
	addq	$56, %rdx
	movq	(%rdx), %rdx
	addq	$8, %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$64, %rax
	movq	-8(%rbp), %rdx
	addq	$64, %rdx
	movq	(%rdx), %rdx
	addq	$9, %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$72, %rax
	movq	-8(%rbp), %rdx
	addq	$72, %rdx
	movq	(%rdx), %rdx
	addq	$10, %rdx
	movq	%rdx, (%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
