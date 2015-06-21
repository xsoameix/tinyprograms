	.file	"p10164_Number_Game.c"
	.section	.rodata
.LC0:
	.string	"[%d] %d %d\n"
	.text
	.globl	dfs
	.type	dfs, @function
dfs:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	-28(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jne	.L2
	jmp	.L1
.L2:
	movl	$0, -8(%rbp)
	jmp	.L4
.L7:
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	movl	$32, %edi
	call	putchar
	addl	$1, -4(%rbp)
.L5:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L6
	movl	-8(%rbp), %eax
	movl	-20(%rbp), %edx
	addl	%edx, %eax
	leal	1(%rax), %ecx
	movl	-8(%rbp), %eax
	movl	-24(%rbp), %edx
	subl	%eax, %edx
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	movl	$0, %eax
	call	sleep
	movq	stdout(%rip), %rax
	movq	%rax, %rdi
	call	fflush
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movl	-8(%rbp), %eax
	movl	-24(%rbp), %ecx
	movl	%ecx, %esi
	subl	%eax, %esi
	movl	-8(%rbp), %eax
	movl	-20(%rbp), %ecx
	addl	%ecx, %eax
	leal	1(%rax), %edi
	movl	-32(%rbp), %eax
	movl	%eax, %ecx
	call	dfs
	addl	$1, -8(%rbp)
.L4:
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L7
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	dfs, .-dfs
	.globl	_____main
	.type	_____main, @function
_____main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$4, %ecx
	movl	$0, %edx
	movl	$4, %esi
	movl	$0, %edi
	call	dfs
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	_____main, .-_____main
	.globl	____main
	.type	____main, @function
____main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-48(%rbp), %rax
	movw	$0, (%rax)
	leaq	-48(%rbp), %rax
	addq	$2, %rax
	movw	$4, (%rax)
	leaq	-48(%rbp), %rax
	addq	$4, %rax
	movw	$0, (%rax)
	movl	$1, -76(%rbp)
	movl	$4, -64(%rbp)
	jmp	.L11
.L17:
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	-48(%rbp), %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	cwtl
	movl	%eax, -60(%rbp)
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	2(%rax), %rdx
	leaq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	cwtl
	movl	%eax, -56(%rbp)
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	4(%rax), %rdx
	leaq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	cwtl
	movl	%eax, -52(%rbp)
	movl	$0, -72(%rbp)
	jmp	.L12
.L13:
	movl	$32, %edi
	call	putchar
	addl	$1, -72(%rbp)
.L12:
	movl	-72(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L13
	movl	-60(%rbp), %ecx
	movl	-56(%rbp), %edx
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	-52(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jne	.L14
	jmp	.L11
.L14:
	movl	$0, -68(%rbp)
	jmp	.L15
.L16:
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	-48(%rbp), %rdx
	addq	%rax, %rdx
	movl	-60(%rbp), %eax
	movl	%eax, %ecx
	movl	-56(%rbp), %eax
	addl	%eax, %ecx
	movl	-68(%rbp), %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movw	%ax, (%rdx)
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	2(%rax), %rdx
	leaq	-48(%rbp), %rax
	addq	%rax, %rdx
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movw	%ax, (%rdx)
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	4(%rax), %rdx
	leaq	-48(%rbp), %rax
	addq	%rax, %rdx
	movl	-52(%rbp), %eax
	addl	$1, %eax
	movw	%ax, (%rdx)
	addl	$1, -68(%rbp)
	addl	$1, -76(%rbp)
.L15:
	movl	-68(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jl	.L16
.L11:
	movl	-76(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -76(%rbp)
	testl	%eax, %eax
	jne	.L17
	movl	$0, %eax
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L19
	call	__stack_chk_fail
.L19:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	____main, .-____main
	.section	.rodata
.LC1:
	.string	"%d"
.LC2:
	.string	"No"
.LC3:
	.string	"Yes"
.LC4:
	.string	"%d%c"
	.text
	.globl	___main
	.type	___main, @function
___main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16789568, %rsp
.L39:
	movl	$1, -16789552(%rbp)
	movl	$1, -16789544(%rbp)
	leaq	-16789556(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	%eax, -16789540(%rbp)
	movl	-16789556(%rbp), %eax
	testl	%eax, %eax
	jne	.L21
	movl	$0, %eax
	jmp	.L40
.L21:
	movl	$0, -16789548(%rbp)
	jmp	.L23
.L24:
	leaq	-16785408(%rbp), %rax
	movl	-16789548(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	%eax, -16789540(%rbp)
	addl	$1, -16789548(%rbp)
.L23:
	movl	-16789556(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-16789548(%rbp), %eax
	jg	.L24
	movl	-16789556(%rbp), %eax
	movl	$0, -16777216(%rbp)
	movl	%eax, -16777212(%rbp)
	movl	$0, -16777208(%rbp)
	movl	$0, -16777204(%rbp)
	jmp	.L25
.L31:
	movl	-16789552(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$16777216, %rax
	movl	(%rax), %eax
	movl	%eax, -16789536(%rbp)
	movl	-16789552(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$16777216, %rax
	movl	4(%rax), %eax
	movl	%eax, -16789532(%rbp)
	movl	-16789552(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$16777216, %rax
	movl	8(%rax), %eax
	movl	%eax, -16789528(%rbp)
	movl	-16789552(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$16777216, %rax
	movl	12(%rax), %eax
	movl	%eax, -16789524(%rbp)
	movl	-16789536(%rbp), %eax
	subl	$1, %eax
	cltq
	movl	-16785408(%rbp,%rax,4), %edx
	movl	-16789528(%rbp), %eax
	cltq
	movl	%edx, -16789520(%rbp,%rax,4)
	movl	-16789556(%rbp), %eax
	cmpl	%eax, -16789528(%rbp)
	jne	.L26
	movl	-16789556(%rbp), %ecx
	movl	-16789524(%rbp), %eax
	cltd
	idivl	%ecx
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L26
	movl	$0, -16789544(%rbp)
	jmp	.L27
.L26:
	movl	-16789556(%rbp), %eax
	cmpl	%eax, -16789528(%rbp)
	jne	.L28
	jmp	.L25
.L28:
	movl	$0, -16789548(%rbp)
	jmp	.L29
.L30:
	movl	-16789532(%rbp), %eax
	movl	-16789536(%rbp), %edx
	addl	%edx, %eax
	subl	-16789548(%rbp), %eax
	movl	-16789548(%rbp), %edx
	leal	1(%rdx), %esi
	movl	-16789528(%rbp), %edx
	leal	1(%rdx), %ecx
	movl	-16789532(%rbp), %edx
	movl	-16789536(%rbp), %edi
	addl	%edi, %edx
	subl	-16789548(%rbp), %edx
	subl	$1, %edx
	movslq	%edx, %rdx
	movl	-16785408(%rbp,%rdx,4), %edi
	movl	-16789524(%rbp), %edx
	addl	%edi, %edx
	movl	-16789552(%rbp), %edi
	movslq	%edi, %rdi
	salq	$4, %rdi
	addq	%rbp, %rdi
	subq	$16777216, %rdi
	movl	%eax, (%rdi)
	movl	-16789552(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$16777216, %rax
	movl	%esi, 4(%rax)
	movl	-16789552(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$16777216, %rax
	movl	%ecx, 8(%rax)
	movl	-16789552(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$16777216, %rax
	movl	%edx, 12(%rax)
	addl	$1, -16789548(%rbp)
	addl	$1, -16789552(%rbp)
.L29:
	movl	-16789548(%rbp), %eax
	cmpl	-16789532(%rbp), %eax
	jl	.L30
.L25:
	movl	-16789552(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -16789552(%rbp)
	testl	%eax, %eax
	jne	.L31
.L27:
	cmpl	$0, -16789544(%rbp)
	je	.L32
	movl	$.LC2, %eax
	jmp	.L33
.L32:
	movl	$.LC3, %eax
.L33:
	movq	%rax, %rdi
	call	puts
	cmpl	$0, -16789544(%rbp)
	jne	.L34
	movl	$0, -16789548(%rbp)
	jmp	.L35
.L38:
	movl	-16789556(%rbp), %eax
	subl	$1, %eax
	cmpl	-16789548(%rbp), %eax
	jle	.L36
	movl	$32, %eax
	jmp	.L37
.L36:
	movl	$10, %eax
.L37:
	movl	-16789548(%rbp), %edx
	addl	$1, %edx
	movslq	%edx, %rdx
	movl	-16789520(%rbp,%rdx,4), %ecx
	movl	%eax, %edx
	movl	%ecx, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -16789548(%rbp)
.L35:
	movl	-16789556(%rbp), %eax
	cmpl	%eax, -16789548(%rbp)
	jl	.L38
.L34:
	jmp	.L39
.L40:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	___main, .-___main
	.section	.rodata
.LC5:
	.string	"i = %d\n"
.LC6:
	.string	"  "
.LC7:
	.string	"%d "
	.text
	.globl	__main
	.type	__main, @function
__main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24224, %rsp
	jmp	.L42
.L63:
	movl	$0, -24208(%rbp)
	jmp	.L43
.L44:
	leaq	-24192(%rbp), %rax
	movl	-24208(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	%eax, -24196(%rbp)
	addl	$1, -24208(%rbp)
.L43:
	movl	-24212(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-24208(%rbp), %eax
	jg	.L44
	leaq	-16000(%rbp), %rax
	movl	$16000, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movl	$0, -24208(%rbp)
	jmp	.L45
.L46:
	movl	-24208(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rbp, %rax
	subq	$16000, %rax
	movl	$1, (%rax)
	addl	$1, -24208(%rbp)
.L45:
	movl	-24212(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-24208(%rbp), %eax
	jge	.L46
	movl	$0, -24208(%rbp)
	jmp	.L47
.L55:
	movl	-24208(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24204(%rbp)
	jmp	.L48
.L54:
	movl	$0, -24200(%rbp)
	jmp	.L49
.L53:
	movl	-24208(%rbp), %eax
	leal	1(%rax), %r8d
	movl	-24200(%rbp), %eax
	movslq	%eax, %rsi
	movl	-24208(%rbp), %eax
	movslq	%eax, %rdx
	movl	-24204(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rcx, %rdx
	salq	$2, %rdx
	addq	%rcx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	addq	%rsi, %rax
	movl	-16000(%rbp,%rax,4), %eax
	testl	%eax, %eax
	jne	.L50
	movl	-24204(%rbp), %eax
	leal	-1(%rax), %edi
	movl	-24208(%rbp), %eax
	cltq
	movl	-24192(%rbp,%rax,4), %eax
	movl	-24200(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	-24212(%rbp), %ecx
	cltd
	idivl	%ecx
	movl	-24212(%rbp), %eax
	addl	%edx, %eax
	movl	-24212(%rbp), %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	movslq	%eax, %rsi
	movl	-24208(%rbp), %eax
	movslq	%eax, %rdx
	movslq	%edi, %rcx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rcx, %rdx
	salq	$2, %rdx
	addq	%rcx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	addq	%rsi, %rax
	movl	-16000(%rbp,%rax,4), %eax
	testl	%eax, %eax
	je	.L51
.L50:
	movl	$1, %ecx
	jmp	.L52
.L51:
	movl	$0, %ecx
.L52:
	movl	-24200(%rbp), %eax
	movslq	%eax, %rdi
	movslq	%r8d, %rdx
	movl	-24204(%rbp), %eax
	movslq	%eax, %rsi
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rsi, %rdx
	salq	$2, %rdx
	addq	%rsi, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	addq	%rdi, %rax
	movl	%ecx, -16000(%rbp,%rax,4)
	addl	$1, -24200(%rbp)
.L49:
	movl	-24212(%rbp), %eax
	cmpl	%eax, -24200(%rbp)
	jl	.L53
	subl	$1, -24204(%rbp)
.L48:
	cmpl	$0, -24204(%rbp)
	jg	.L54
	addl	$1, -24208(%rbp)
.L47:
	movl	-24212(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-24208(%rbp), %eax
	jg	.L55
	movl	$0, -24208(%rbp)
	jmp	.L56
.L61:
	movl	-24208(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -24204(%rbp)
	jmp	.L57
.L60:
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -24200(%rbp)
	jmp	.L58
.L59:
	movl	-24200(%rbp), %eax
	movslq	%eax, %rsi
	movl	-24208(%rbp), %eax
	movslq	%eax, %rdx
	movl	-24204(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rcx, %rdx
	salq	$2, %rdx
	addq	%rcx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	addq	%rsi, %rax
	movl	-16000(%rbp,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -24200(%rbp)
.L58:
	movl	-24212(%rbp), %eax
	cmpl	%eax, -24200(%rbp)
	jl	.L59
	movl	$10, %edi
	call	putchar
	addl	$1, -24204(%rbp)
.L57:
	movl	-24212(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-24204(%rbp), %eax
	jge	.L60
	addl	$1, -24208(%rbp)
.L56:
	movl	-24212(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-24208(%rbp), %eax
	jge	.L61
.L42:
	leaq	-24212(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	cmpl	$1, %eax
	jne	.L62
	movl	-24212(%rbp), %eax
	testl	%eax, %eax
	jne	.L63
.L62:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	__main, .-__main
	.section	.rodata
.LC8:
	.string	" "
.LC9:
	.string	""
.LC10:
	.string	"%d%s"
	.text
	.globl	_main
	.type	_main, @function
_main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$538714144, %rsp
	jmp	.L66
.L86:
	movl	$0, -538714128(%rbp)
	jmp	.L67
.L68:
	leaq	-538714112(%rbp), %rax
	movl	-538714128(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	%eax, -538714116(%rbp)
	addl	$1, -538714128(%rbp)
.L67:
	movl	-538714132(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-538714128(%rbp), %eax
	jg	.L68
	leaq	-538705920(%rbp), %rax
	movl	$2097152, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-536608768(%rbp), %rax
	movl	$536608768, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movb	$1, -538705920(%rbp)
	movl	$0, -538714128(%rbp)
	jmp	.L69
.L75:
	movl	-538714128(%rbp), %eax
	leal	1(%rax), %edx
	movl	-538714132(%rbp), %eax
	cmpl	%eax, %edx
	cmovle	%edx, %eax
	movl	%eax, -538714124(%rbp)
	jmp	.L70
.L74:
	movl	$0, -538714120(%rbp)
	jmp	.L71
.L73:
	movl	-538714120(%rbp), %eax
	cltq
	movl	-538714124(%rbp), %edx
	movslq	%edx, %rdx
	salq	$10, %rdx
	addq	%rbp, %rdx
	addq	%rdx, %rax
	subq	$538705920, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L72
	movl	-538714124(%rbp), %eax
	leal	-1(%rax), %esi
	movl	-538714128(%rbp), %eax
	cltq
	movl	-538714112(%rbp,%rax,4), %eax
	movl	-538714120(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	-538714132(%rbp), %ecx
	cltd
	idivl	%ecx
	movl	-538714132(%rbp), %eax
	addl	%edx, %eax
	movl	-538714132(%rbp), %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	cltq
	movslq	%esi, %rdx
	salq	$10, %rdx
	addq	%rbp, %rdx
	addq	%rdx, %rax
	subq	$538705920, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L72
	movl	-538714120(%rbp), %eax
	cltq
	movl	-538714124(%rbp), %edx
	movslq	%edx, %rdx
	salq	$10, %rdx
	addq	%rbp, %rdx
	addq	%rdx, %rax
	subq	$538705920, %rax
	movb	$1, (%rax)
	movl	-538714120(%rbp), %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movslq	%eax, %rdx
	movl	-538714128(%rbp), %ecx
	movslq	%ecx, %rsi
	movl	-538714124(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$11, %rsi
	addq	%rsi, %rcx
	salq	$7, %rcx
	addq	%rbp, %rcx
	addq	%rcx, %rdx
	subq	$536608768, %rdx
	movzbl	(%rdx), %esi
	movl	-538714120(%rbp), %edx
	movl	%edx, %ecx
	sarl	$31, %ecx
	shrl	$29, %ecx
	addl	%ecx, %edx
	andl	$7, %edx
	subl	%ecx, %edx
	movl	$1, %edi
	movl	%edx, %ecx
	sall	%cl, %edi
	movl	%edi, %edx
	orl	%esi, %edx
	cltq
	movl	-538714128(%rbp), %ecx
	movslq	%ecx, %rsi
	movl	-538714124(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$11, %rsi
	addq	%rsi, %rcx
	salq	$7, %rcx
	addq	%rbp, %rcx
	addq	%rcx, %rax
	subq	$536608768, %rax
	movb	%dl, (%rax)
.L72:
	addl	$1, -538714120(%rbp)
.L71:
	movl	-538714132(%rbp), %eax
	cmpl	%eax, -538714120(%rbp)
	jl	.L73
	subl	$1, -538714124(%rbp)
.L70:
	cmpl	$0, -538714124(%rbp)
	jg	.L74
	addl	$1, -538714128(%rbp)
.L69:
	movl	-538714132(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	cmpl	-538714128(%rbp), %eax
	jg	.L75
	movl	-538714132(%rbp), %eax
	subl	$1, %eax
	addl	%eax, %eax
	movl	%eax, -538714128(%rbp)
	movl	-538714132(%rbp), %eax
	movl	%eax, -538714124(%rbp)
	jmp	.L76
.L79:
	movl	-538714124(%rbp), %eax
	cltq
	movl	-538714128(%rbp), %edx
	movslq	%edx, %rdx
	salq	$11, %rdx
	addq	%rdx, %rax
	salq	$7, %rax
	addq	%rbp, %rax
	subq	$536608768, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L77
	jmp	.L78
.L77:
	subl	$1, -538714128(%rbp)
.L76:
	cmpl	$0, -538714128(%rbp)
	jns	.L79
.L78:
	movl	$.LC3, %edi
	call	puts
	movl	$0, -538714120(%rbp)
	jmp	.L80
.L84:
	movl	-538714120(%rbp), %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	cltq
	movl	-538714128(%rbp), %edx
	movslq	%edx, %rcx
	movl	-538714124(%rbp), %edx
	movslq	%edx, %rdx
	salq	$11, %rcx
	addq	%rcx, %rdx
	salq	$7, %rdx
	addq	%rbp, %rdx
	addq	%rdx, %rax
	subq	$536608768, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %esi
	movl	-538714120(%rbp), %eax
	cltd
	shrl	$29, %edx
	addl	%edx, %eax
	andl	$7, %eax
	subl	%edx, %eax
	movl	%eax, %ecx
	sarl	%cl, %esi
	movl	%esi, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L81
	subl	$1, -538714124(%rbp)
	cmpl	$0, -538714124(%rbp)
	je	.L82
	movl	$.LC8, %eax
	jmp	.L83
.L82:
	movl	$.LC9, %eax
.L83:
	movl	-538714128(%rbp), %edx
	movslq	%edx, %rdx
	movl	-538714112(%rbp,%rdx,4), %ecx
	movq	%rax, %rdx
	movl	%ecx, %esi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	printf
	movl	-538714128(%rbp), %eax
	cltq
	movl	-538714112(%rbp,%rax,4), %eax
	movl	-538714120(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	-538714132(%rbp), %ecx
	cltd
	idivl	%ecx
	movl	-538714132(%rbp), %eax
	addl	%edx, %eax
	movl	-538714132(%rbp), %ecx
	cltd
	idivl	%ecx
	movl	%edx, -538714120(%rbp)
.L81:
	subl	$1, -538714128(%rbp)
.L80:
	cmpl	$0, -538714128(%rbp)
	jns	.L84
	movl	$10, %edi
	call	putchar
.L66:
	leaq	-538714132(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	cmpl	$1, %eax
	jne	.L85
	movl	-538714132(%rbp), %eax
	testl	%eax, %eax
	jne	.L86
.L85:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	_main, .-_main
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
	jmp	.L89
.L108:
	movl	$0, i.3037(%rip)
	jmp	.L90
.L91:
	movl	i.3037(%rip), %eax
	cltq
	salq	$2, %rax
	addq	$n.3034, %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	%eax, _.3040(%rip)
	movl	i.3037(%rip), %eax
	addl	$1, %eax
	movl	%eax, i.3037(%rip)
.L90:
	movl	l.3033(%rip), %eax
	addl	%eax, %eax
	leal	-1(%rax), %edx
	movl	i.3037(%rip), %eax
	cmpl	%eax, %edx
	jg	.L91
	movl	$4198400, %edx
	movl	$0, %esi
	movl	$d.3035, %edi
	call	memset
	movl	$1, d.3035(%rip)
	movl	l.3033(%rip), %eax
	subl	$1, %eax
	leal	(%rax,%rax), %edx
	movl	l.3033(%rip), %eax
	movl	%edx, s.3031(%rip)
	movl	%eax, s.3031+4(%rip)
	movl	$0, s.3031+8(%rip)
	movl	$1, si.3036(%rip)
	jmp	.L92
.L102:
	movl	j.3038(%rip), %edx
	movl	k.3039(%rip), %eax
	cltq
	movslq	%edx, %rdx
	salq	$10, %rdx
	addq	%rdx, %rax
	movl	d.3035(,%rax,4), %eax
	testl	%eax, %eax
	jne	.L94
	movl	si.3036(%rip), %eax
	movl	%eax, %edx
	leal	1(%rdx), %eax
	movl	%eax, si.3036(%rip)
	movl	i.3037(%rip), %eax
	leal	-1(%rax), %edi
	movl	l.3033(%rip), %esi
	movslq	%edx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$2, %rax
	addq	$s.3031, %rax
	movl	%edi, (%rax)
	movslq	%edx, %rcx
	movq	%rcx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	salq	$2, %rax
	addq	$s.3031, %rax
	movl	%esi, 4(%rax)
	movslq	%edx, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	$s.3031, %rax
	movl	$0, 8(%rax)
	nop
.L94:
	movl	j.3038(%rip), %edx
	movl	k.3039(%rip), %eax
	cltq
	movslq	%edx, %rdx
	salq	$10, %rdx
	addq	%rdx, %rax
	movl	d.3035(,%rax,4), %eax
	testl	%eax, %eax
	jne	.L95
	movl	j.3038(%rip), %eax
	leal	-1(%rax), %esi
	movl	k.3039(%rip), %edx
	movl	i.3037(%rip), %eax
	cltq
	movl	n.3034(,%rax,4), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	l.3033(%rip), %ecx
	cltd
	idivl	%ecx
	movl	l.3033(%rip), %eax
	addl	%edx, %eax
	movl	l.3033(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	cltq
	movslq	%esi, %rdx
	salq	$10, %rdx
	addq	%rdx, %rax
	movl	d.3035(,%rax,4), %eax
	testl	%eax, %eax
	je	.L95
	movl	j.3038(%rip), %ecx
	movl	k.3039(%rip), %eax
	movl	i.3037(%rip), %edx
	addl	$1, %edx
	cltq
	movslq	%ecx, %rcx
	salq	$10, %rcx
	addq	%rcx, %rax
	movl	%edx, d.3035(,%rax,4)
.L95:
	movl	i.3037(%rip), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$0, j.3038(%rip)
	jmp	.L96
.L99:
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$0, k.3039(%rip)
	jmp	.L97
.L98:
	movl	j.3038(%rip), %edx
	movl	k.3039(%rip), %eax
	cltq
	movslq	%edx, %rdx
	salq	$10, %rdx
	addq	%rdx, %rax
	movl	d.3035(,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movl	k.3039(%rip), %eax
	addl	$1, %eax
	movl	%eax, k.3039(%rip)
.L97:
	movl	k.3039(%rip), %edx
	movl	l.3033(%rip), %eax
	cmpl	%eax, %edx
	jl	.L98
	movl	$10, %edi
	call	putchar
	movl	j.3038(%rip), %eax
	addl	$1, %eax
	movl	%eax, j.3038(%rip)
.L96:
	movl	j.3038(%rip), %edx
	movl	l.3033(%rip), %eax
	cmpl	%eax, %edx
	jle	.L99
.L92:
	movl	si.3036(%rip), %eax
	leal	-1(%rax), %edx
	movl	%edx, si.3036(%rip)
	testl	%eax, %eax
	je	.L101
	movl	si.3036(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	$s.3031, %rax
	movq	(%rax), %rdx
	movq	%rdx, t.3032(%rip)
	movl	8(%rax), %eax
	movl	%eax, t.3032+8(%rip)
	nop
.L101:
	movl	t.3032(%rip), %eax
	movl	%eax, i.3037(%rip)
	movl	t.3032+4(%rip), %eax
	movl	%eax, j.3038(%rip)
	movl	t.3032+8(%rip), %eax
	movl	%eax, k.3039(%rip)
	movl	k.3039(%rip), %eax
	testl	%eax, %eax
	jne	.L102
	movl	$.LC3, %edi
	call	puts
	movl	l.3033(%rip), %eax
	movl	%eax, j.3038(%rip)
	movl	$0, k.3039(%rip)
	jmp	.L103
.L106:
	movl	j.3038(%rip), %edx
	movl	k.3039(%rip), %eax
	cltq
	movslq	%edx, %rdx
	salq	$10, %rdx
	addq	%rdx, %rax
	movl	d.3035(,%rax,4), %eax
	movl	%eax, i.3037(%rip)
	movl	i.3037(%rip), %eax
	testl	%eax, %eax
	je	.L103
	movl	j.3038(%rip), %eax
	subl	$1, %eax
	movl	%eax, j.3038(%rip)
	movl	j.3038(%rip), %eax
	testl	%eax, %eax
	je	.L104
	movl	$.LC8, %eax
	jmp	.L105
.L104:
	movl	$.LC9, %eax
.L105:
	movl	i.3037(%rip), %edx
	subl	$1, %edx
	movslq	%edx, %rdx
	movl	n.3034(,%rdx,4), %ecx
	movq	%rax, %rdx
	movl	%ecx, %esi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	printf
	movl	k.3039(%rip), %edx
	movl	i.3037(%rip), %eax
	subl	$1, %eax
	cltq
	movl	n.3034(,%rax,4), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	l.3033(%rip), %ecx
	cltd
	idivl	%ecx
	movl	l.3033(%rip), %eax
	addl	%edx, %eax
	movl	l.3033(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	movl	%eax, k.3039(%rip)
.L103:
	movl	j.3038(%rip), %eax
	testl	%eax, %eax
	jne	.L106
	movl	$10, %edi
	call	putchar
.L89:
	movl	$l.3033, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	cmpl	$1, %eax
	jne	.L107
	movl	l.3033(%rip), %eax
	testl	%eax, %eax
	jne	.L108
.L107:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.local	i.3037
	.comm	i.3037,4,4
	.local	n.3034
	.comm	n.3034,8188,32
	.local	_.3040
	.comm	_.3040,4,4
	.local	l.3033
	.comm	l.3033,4,4
	.local	d.3035
	.comm	d.3035,4198400,32
	.local	s.3031
	.comm	s.3031,12300,32
	.local	si.3036
	.comm	si.3036,4,4
	.local	j.3038
	.comm	j.3038,4,4
	.local	k.3039
	.comm	k.3039,4,4
	.local	t.3032
	.comm	t.3032,12,4
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
