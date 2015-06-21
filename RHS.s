	.file	"RHS.c"
	.text
	.globl	arol
	.type	arol, @function
arol:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	-104(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movl	4(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -72(%rbp)
	movq	-80(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	%rdx, -64(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -56(%rbp)
	movl	16(%rax), %eax
	movl	%eax, -48(%rbp)
	movq	-72(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	%rdx, -32(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movl	16(%rax), %eax
	movl	%eax, -16(%rbp)
	movq	-104(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -84(%rbp)
	movq	-80(%rbp), %rax
	movl	4(%rax), %edx
	movq	-104(%rbp), %rax
	movl	%edx, (%rax)
	movq	-72(%rbp), %rax
	movl	(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, 4(%rax)
	movq	-72(%rbp), %rax
	movl	-84(%rbp), %edx
	movl	%edx, (%rax)
	movl	-24(%rbp), %edx
	movl	-56(%rbp), %eax
	cmpl	%eax, %edx
	cmovge	%edx, %eax
	leal	1(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-80(%rbp), %rax
	movl	8(%rax), %edx
	movq	-72(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	jl	.L2
	movq	-80(%rbp), %rax
	movl	8(%rax), %eax
	leal	1(%rax), %edx
	movq	-72(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-72(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	je	.L5
.L2:
	nop
.L5:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	arol, .-arol
	.globl	aror
	.type	aror, @function
aror:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	-104(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -72(%rbp)
	movq	-80(%rbp), %rax
	movl	4(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	%rdx, -64(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -56(%rbp)
	movl	16(%rax), %eax
	movl	%eax, -48(%rbp)
	movq	-72(%rbp), %rax
	movl	4(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	%rdx, -32(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movl	16(%rax), %eax
	movl	%eax, -16(%rbp)
	movq	-104(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -84(%rbp)
	movq	-80(%rbp), %rax
	movl	(%rax), %edx
	movq	-104(%rbp), %rax
	movl	%edx, (%rax)
	movq	-72(%rbp), %rax
	movl	4(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, (%rax)
	movq	-72(%rbp), %rax
	movl	-84(%rbp), %edx
	movl	%edx, 4(%rax)
	movl	-24(%rbp), %edx
	movl	-56(%rbp), %eax
	cmpl	%eax, %edx
	cmovge	%edx, %eax
	leal	1(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-80(%rbp), %rax
	movl	8(%rax), %edx
	movq	-72(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	jl	.L7
	movq	-80(%rbp), %rax
	movl	8(%rax), %eax
	leal	1(%rax), %edx
	movq	-72(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-72(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	je	.L10
.L7:
	nop
.L10:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	aror, .-aror
	.globl	ains
	.type	ains, @function
ains:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movl	%edi, -148(%rbp)
	movl	%esi, -152(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -168(%rbp)
	movq	%r8, -176(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -16(%rbp)
	movq	-160(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -48(%rbp)
	movl	$1, -144(%rbp)
	movl	$0, -140(%rbp)
	jmp	.L12
.L31:
	movq	-176(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %ecx
	movq	-176(%rbp), %rdx
	movl	%ecx, (%rdx)
	movq	-128(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-128(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	movl	$0, 4(%rax)
	movl	$1, 8(%rax)
	movl	-148(%rbp), %edx
	movl	%edx, 12(%rax)
	movl	-152(%rbp), %edx
	movl	%edx, 16(%rax)
	movl	$1, -140(%rbp)
	jmp	.L12
.L13:
	cmpl	$0, -140(%rbp)
	je	.L14
	cmpl	$0, -136(%rbp)
	je	.L15
	movq	-120(%rbp), %rax
	jmp	.L16
.L15:
	movq	-120(%rbp), %rax
	addq	$4, %rax
.L16:
	movl	-144(%rbp), %edx
	addl	$1, %edx
	movslq	%edx, %rdx
	movl	-48(%rbp,%rdx,4), %edx
	movl	%edx, (%rax)
	movq	-120(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	%rdx, -112(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -104(%rbp)
	movl	16(%rax), %eax
	movl	%eax, -96(%rbp)
	movl	-104(%rbp), %ecx
	movq	-120(%rbp), %rax
	movl	4(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	%rdx, -80(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -72(%rbp)
	movl	16(%rax), %eax
	movl	%eax, -64(%rbp)
	movl	-72(%rbp), %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -132(%rbp)
	cmpl	$0, -132(%rbp)
	jle	.L17
	movl	-104(%rbp), %eax
	addl	$1, %eax
	jmp	.L18
.L17:
	movl	-72(%rbp), %eax
	addl	$1, %eax
.L18:
	movq	-120(%rbp), %rdx
	movl	%eax, 8(%rdx)
	cmpl	$-1, -132(%rbp)
	jge	.L22
	movl	-68(%rbp), %eax
	cmpl	-148(%rbp), %eax
	jle	.L21
	movq	-120(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	-168(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	aror
	testl	%eax, %eax
	je	.L21
	nop
.L21:
	movq	-168(%rbp), %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	arol
	testl	%eax, %eax
	je	.L22
	nop
.L22:
	cmpl	$1, -132(%rbp)
	jle	.L12
	movl	-100(%rbp), %eax
	cmpl	-148(%rbp), %eax
	jge	.L25
	movq	-120(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	arol
	testl	%eax, %eax
	je	.L25
	nop
.L25:
	movq	-168(%rbp), %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	aror
	testl	%eax, %eax
	je	.L12
	jmp	.L12
.L14:
	addl	$1, -144(%rbp)
	movl	-144(%rbp), %edx
	leal	1(%rdx), %eax
	movl	%eax, -144(%rbp)
	cmpl	$0, -136(%rbp)
	je	.L27
	movq	-120(%rbp), %rax
	movl	(%rax), %eax
	jmp	.L28
.L27:
	movq	-120(%rbp), %rax
	movl	4(%rax), %eax
.L28:
	movslq	%edx, %rdx
	movl	%eax, -48(%rbp,%rdx,4)
.L12:
	movl	-144(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -144(%rbp)
	testl	%eax, %eax
	je	.L29
	movl	-144(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	-48(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	-148(%rbp), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -136(%rbp)
	movq	-120(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jne	.L13
	jmp	.L31
.L29:
	movl	-48(%rbp), %edx
	movq	-160(%rbp), %rax
	movl	%edx, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	ains, .-ains
	.globl	afet
	.type	afet, @function
afet:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -8(%rbp)
	movq	%rcx, -24(%rbp)
	jmp	.L33
.L37:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	12(%rax), %eax
	cmpl	-4(%rbp), %eax
	jle	.L34
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	jmp	.L35
.L34:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %eax
.L35:
	movl	%eax, -8(%rbp)
.L33:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %eax
	cmpl	$1, %eax
	jle	.L36
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	12(%rax), %eax
	cmpl	-4(%rbp), %eax
	jne	.L37
.L36:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	12(%rax), %eax
	cmpl	-4(%rbp), %eax
	jne	.L38
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	16(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	movl	$1, %eax
	jmp	.L39
.L38:
	movl	$0, %eax
.L39:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	afet, .-afet
	.section	.rodata
.LC0:
	.string	"[%d %d]"
.LC1:
	.string	""
.LC2:
	.string	"[%d %d %d %d %d]"
	.text
	.globl	tins
	.type	tins, @function
tins:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L42
.L43:
	addq	$1, -24(%rbp)
.L42:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movq	-40(%rbp), %rcx
	leaq	-8(%rbp), %rsi
	movl	%eax, %edi
	call	afet
	testl	%eax, %eax
	jne	.L43
	jmp	.L44
.L45:
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdx
	movq	-48(%rbp), %rax
	movl	(%rax), %esi
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -24(%rbp)
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movq	-56(%rbp), %rdi
	movq	-40(%rbp), %rcx
	movq	%rdi, %r8
	movl	%eax, %edi
	call	ains
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %ecx
	movq	-48(%rbp), %rdx
	movl	%ecx, (%rdx)
	movl	%eax, -8(%rbp)
.L44:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L45
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	4(%rdx), %eax
	leal	1(%rax), %ecx
	movl	%ecx, 4(%rdx)
	testl	%eax, %eax
	jne	.L45
	movl	$0, -4(%rbp)
	jmp	.L46
.L47:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L46:
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	cmpl	-4(%rbp), %eax
	jg	.L47
	movl	$.LC1, %edi
	call	puts
	testl	%eax, %eax
	je	.L47
	movl	$0, -4(%rbp)
	jmp	.L48
.L49:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	16(%rax), %r8d
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	12(%rax), %edi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %esi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%r8d, %r9d
	movl	%edi, %r8d
	movl	%esi, %edx
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L48:
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	cmpl	-4(%rbp), %eax
	jg	.L49
	movl	$.LC1, %edi
	call	puts
	testl	%eax, %eax
	je	.L49
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	tins, .-tins
	.globl	cmp
	.type	cmp, @function
cmp:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$2, %rax
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	$2, %rax
	movq	%rax, -8(%rbp)
	jmp	.L51
.L53:
	addq	$1, -16(%rbp)
	addq	$1, -8(%rbp)
.L51:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L52
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L53
.L52:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edx
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	cmp, .-cmp
	.section	.rodata
.LC3:
	.string	"E:U"
.LC4:
	.string	"U:T"
.LC5:
	.string	"U:U+T"
.LC6:
	.string	"T:V"
.LC7:
	.string	"V:F"
.LC8:
	.string	"V:V*F"
.LC9:
	.string	"F:i"
.LC10:
	.string	"F:(E)"
.LC11:
	.string	"\t\b"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$2896, %rsp
	movq	$.LC3, -2864(%rbp)
	movq	$.LC4, -2856(%rbp)
	movq	$.LC5, -2848(%rbp)
	movq	$.LC6, -2840(%rbp)
	movq	$.LC7, -2832(%rbp)
	movq	$.LC8, -2824(%rbp)
	movq	$.LC9, -2816(%rbp)
	movq	$.LC10, -2808(%rbp)
	movl	$8, -2872(%rbp)
	movl	-2872(%rbp), %eax
	movslq	%eax, %rdx
	leaq	-2864(%rbp), %rax
	movl	$cmp, %ecx
	movl	$8, %esi
	movq	%rax, %rdi
	call	qsort
	movl	$0, -2876(%rbp)
	jmp	.L56
.L57:
	movl	-2876(%rbp), %eax
	cltq
	movq	-2864(%rbp,%rax,8), %rax
	movq	%rax, %rdi
	call	puts
	addl	$1, -2876(%rbp)
.L56:
	movl	-2876(%rbp), %eax
	cmpl	-2872(%rbp), %eax
	jl	.L57
	leaq	-2800(%rbp), %rsi
	movl	$0, %eax
	movl	$100, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	leaq	-2000(%rbp), %rsi
	movl	$0, %eax
	movl	$250, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	$1, -2868(%rbp)
	movl	$0, -2884(%rbp)
	movl	$1, -2880(%rbp)
	leaq	-2880(%rbp), %rsi
	leaq	-2884(%rbp), %rcx
	leaq	-2000(%rbp), %rdx
	leaq	-2800(%rbp), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	movl	$.LC11, %edi
	call	tins
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
