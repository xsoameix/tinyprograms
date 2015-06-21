	.file	"xor.c"
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
	movq	$1, -48(%rbp) # a
	movq	$2, -40(%rbp)
	movq	$3, -32(%rbp) # b
	movq	$4, -24(%rbp)
	movq	$5, -16(%rbp) # c
	movq	$6, -8(%rbp)
	movq	$0, -56(%rbp) # i
	movq	-56(%rbp), %rax
	movq	-48(%rbp,%rax,8), %rcx # a[i]
	movq	-56(%rbp), %rax
	movq	-32(%rbp,%rax,8), %rsi # b[i]
	movq	-56(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -56(%rbp) # i++
	movq	-16(%rbp,%rax,8), %rax # c[i]
	subq	%rax, %rsi # b[i] - c[i]
	movq	%rsi, %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, -32(%rbp,%rax,8) # b[i+1] = b[i] - c[i]
	movq	-56(%rbp), %rax
	movq	-32(%rbp,%rax,8), %rax # b[i+1]
	leaq	(%rcx,%rax), %rdx # a[i] + b[i+1]
	movq	-56(%rbp), %rax
	movq	%rdx, -48(%rbp,%rax,8) # a[i+1] = a[i] + b[i+1]
                                   # a[i] += b[i] -= c[i++];
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
