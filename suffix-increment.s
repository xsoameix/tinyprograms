	.file	"suffix-increment.c"
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
	subq	$64, %rsp
	movl	$0, -56(%rbp)
	movl	$2, -52(%rbp)
	movl	-56(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -56(%rbp)
	movl	-56(%rbp), %edx
	leal	-2(%rdx), %esi
	movl	-56(%rbp), %edx
	leal	-1(%rdx), %ecx
	movslq	%eax, %rdx
	movl	%esi, -48(%rbp,%rdx,8)
	cltq
	movl	%ecx, -44(%rbp,%rax,8)
	jmp	.L2
.L4:
	movl	$97, %edi
	call	putchar
.L2:
	movl	-56(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -56(%rbp)
	testl	%eax, %eax
	je	.L3
	movl	-52(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,8), %eax
	movl	%eax, -56(%rbp)
	cmpl	$0, -56(%rbp)
	jne	.L4
.L3:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
