main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, -12(%rbp)
	jmp	.L2
.L3:
	movl	$2, -8(%rbp)
	addl	$1, -12(%rbp)
.L2:
	cmpl	$9, -12(%rbp)
	jle	.L3
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	$0, %eax
	popq	%rbp
	ret
