	.file	"return_struct.c"
	.text
	.globl	return_foo
	.type	return_foo, @function
return_foo:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %eax
	movl	$6, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	movq	-8(%rbp), %rax
	movq	$2, 8(%rax)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	return_foo, .-return_foo
	.globl	call_foo
	.type	call_foo, @function
call_foo:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	return_foo
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	call_foo, .-call_foo
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
