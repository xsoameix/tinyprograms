	.file	"no-stdin.c"
	.section	.rodata
.LC0:
	.string	"len %d\n"
.LC1:
	.string	"i %d\n"
.LC2:
	.string	"%02X "
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
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$1684234849, -32(%rbp)
	movb	$0, -28(%rbp)
	movl	$0, -40(%rbp)
	movl	$5, -36(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L2
.L3:
	movl	-40(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L2:
	movl	-40(%rbp), %eax
	cltq
	movzbl	-32(%rbp,%rax), %esi
	movl	-40(%rbp), %eax
	movl	-36(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	leal	-3(%rax), %edx
	movl	-40(%rbp), %eax
	movl	-36(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	subl	$3, %eax
	cltq
	movzbl	-32(%rbp,%rax), %edi
	movl	-40(%rbp), %eax
	cltq
	movzbl	-32(%rbp,%rax), %r8d
	movl	-40(%rbp), %eax
	leal	1(%rax), %ecx
	movl	%ecx, -40(%rbp) # i++
	movl	-36(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	subl	$2, %eax
	cltq
	movzbl	-32(%rbp,%rax), %eax # s[l-i-2]
	movl	%r8d, %ecx
	xorl	%eax, %ecx # s[i] ^ s[l-i-2]
	movl	-40(%rbp), %eax
	cltq
	movb	%cl, -32(%rbp,%rax) # s[i+1] = s[i] ^ s[l-i-2]
	movl	-40(%rbp), %eax
	cltq
	movzbl	-32(%rbp,%rax), %eax
	xorl	%eax, %edi # s[l-i-3] ^ s[i+1]
	movl	%edi, %ecx
	movslq	%edx, %rax
	movb	%cl, -32(%rbp,%rax) # s[l-i-3] = s[l-i-3] ^ s[i+1]
	movslq	%edx, %rax
	movzbl	-32(%rbp,%rax), %eax
	xorl	%eax, %esi
	movl	%esi, %edx
	movl	-40(%rbp), %eax
	cltq
	movb	%dl, -32(%rbp,%rax)
	movl	-36(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	subl	$1, %eax
	cmpl	-40(%rbp), %eax
	jg	.L3
	movzbl	-32(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movzbl	-31(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movzbl	-30(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movzbl	-29(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movzbl	-28(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L5
	call	__stack_chk_fail
.L5:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
