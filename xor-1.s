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
	movq	$1, -32(%rbp)
	movq	$2, -24(%rbp)
	movq	$3, -16(%rbp)
	movq	$4, -8(%rbp) # a
	movq	$0, -40(%rbp) # i
	movq	-40(%rbp), %rax
	movq	-32(%rbp,%rax,8), %rcx # a[i]
	movq	-40(%rbp), %rax
	movq	-32(%rbp,%rax,8), %rsi # a[i]
	movq	-40(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -40(%rbp) # i++
	movq	-32(%rbp,%rax,8), %rax # a[i]
	subq	%rax, %rsi # a[i] - a[i]
	movq	%rsi, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, -32(%rbp,%rax,8) # a[i+1] = a[i] - a[i]
	movq	-40(%rbp), %rax
	movq	-32(%rbp,%rax,8), %rax # a[i+1]
	leaq	(%rcx,%rax), %rdx # a[i] + a[i+1]
	movq	-40(%rbp), %rax
	movq	%rdx, -32(%rbp,%rax,8) # a[i+1] = a[i] + a[i+1]
                                   # a[i] += a[i] -= a[i++];
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
