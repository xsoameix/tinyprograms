	.file	"local.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, -96(%rbp)
	movl	$0, -92(%rbp)
	movl	$0, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, -48(%rbp)
	movl	$2, -40(%rbp)
	movl	$2, -80(%rbp)
	movl	$0, -76(%rbp)
	movl	$0, -72(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	movl	$2, -24(%rbp)
	movl	$3, -64(%rbp)
	movl	$0, -60(%rbp)
	movl	$0, -56(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$2, -8(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
