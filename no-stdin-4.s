	.file	"no-stdin.c"
	.section	.rodata
.LC0:
	.string	"len %lld\n"
.LC1:
	.string	"i %lld\n"
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
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$1684234849, -32(%rbp)
	movb	$0, -28(%rbp)
	movq	$0, -64(%rbp)
	movq	$5, -56(%rbp)
	movq	$1, -48(%rbp)
	movq	$2, -40(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L2
.L3:
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L2:
	movq	-64(%rbp), %rax
	movq	-48(%rbp,%rax,8), %rcx
	leaq	-32(%rbp), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %esi
	movq	-64(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -64(%rbp) # i++
	movq	-56(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	subq	$2, %rax
	movzbl	-32(%rbp,%rax), %eax
	xorl	%esi, %eax # s[l-i-2] ^ s[i]
	leaq	-32(%rbp), %rsi
	movq	-64(%rbp), %rdx
	addq	%rsi, %rdx
	movb	%al, (%rdx) # s[i+1] = s[l-i-2] ^ s[i]
	leaq	-32(%rbp), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	xorq	%rax, %rcx # c[i] ^ s[i+1]
	movq	%rcx, %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, -48(%rbp,%rax,8) # c[i+1] = c[i] ^ s[i+1]
                                   # c[i] ^= s[i] ^= s[l-i++-2]
	movq	-56(%rbp), %rax
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rdx, %rax
	sarq	%rax
	subq	$1, %rax
	cmpq	-64(%rbp), %rax
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
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
