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
	movq	-56(%rbp), %rdx
	movq	%rdx, %rsi
	subq	%rax, %rsi
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	movzbl	-32(%rbp,%rax), %edi
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rcx
	subq	%rdx, %rcx
	movq	%rcx, %rdx
	movzbl	-32(%rbp,%rdx), %r8d
	movq	-64(%rbp), %rdx
	leaq	1(%rdx), %rcx
	movq	%rcx, -64(%rbp) # i++
	movq	-56(%rbp), %rcx
	subq	%rdx, %rcx
	movq	%rcx, %rdx
	subq	$2, %rdx
	movzbl	-32(%rbp,%rdx), %edx
	xorl	%r8d, %edx
	movb	%dl, -32(%rbp,%rax) # s[l-i] = s[l-i] ^ s[l-i-2]
	movzbl	-32(%rbp,%rax), %eax
	xorl	%edi, %eax # s[l-i] ^ s[l-i]
	movb	%al, -32(%rbp,%rsi) # s[l-i] = s[l-i] ^ s[l-i]
                                # s[l-i] ^= s[l-i] ^= s[l-i++-2]
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
