	.file	"perfect_number.c"
	.text
	.globl	is_prime
	.type	is_prime, @function
is_prime:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	cmpl	$1, -20(%rbp)
	jg	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	cvtsi2sd	-20(%rbp), %xmm0
	call	sqrt
	cvttsd2si	%xmm0, %eax
	movl	%eax, -4(%rbp)
	movl	$2, -8(%rbp)
	jmp	.L4
.L6:
	movl	-20(%rbp), %eax
	cltd
	idivl	-8(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L5
	movl	$0, %eax
	jmp	.L3
.L5:
	addl	$1, -8(%rbp)
.L4:
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jle	.L6
	movl	$1, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	is_prime, .-is_prime
	.globl	is_perfect
	.type	is_perfect, @function
is_perfect:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movl	$2, -8(%rbp)
.L12:
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	is_prime
	testl	%eax, %eax
	jne	.L8
	jmp	.L9
.L8:
	movl	-8(%rbp), %eax
	subl	$1, %eax
	cvtsi2sd	%eax, %xmm0
	movabsq	$4611686018427387904, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, -32(%rbp)
	movsd	-32(%rbp), %xmm0
	call	pow
	movsd	%xmm0, -32(%rbp)
	cvtsi2sd	-8(%rbp), %xmm0
	movabsq	$4611686018427387904, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	call	pow
	movsd	.LC1(%rip), %xmm1
	subsd	%xmm1, %xmm0
	mulsd	-32(%rbp), %xmm0
	cvttsd2siq	%xmm0, %rax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jae	.L10
	movl	$0, %eax
	jmp	.L11
.L10:
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jne	.L9
	movl	$1, %eax
	jmp	.L11
.L9:
	addl	$1, -8(%rbp)
	jmp	.L12
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	is_perfect, .-is_perfect
	.section	.rodata
.LC2:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	jmp	.L14
.L16:
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	is_perfect
	testl	%eax, %eax
	je	.L15
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
.L15:
	addl	$1, -4(%rbp)
.L14:
	cmpl	$33550337, -4(%rbp)
	jle	.L16
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
