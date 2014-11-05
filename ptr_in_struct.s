	.file	"ptr_in_struct.c"
	.data
	.align 4
	.type	__compound_literal.0, @object
	.size	__compound_literal.0, 8
__compound_literal.0:
	.long	1
	.long	2
	.globl	foo
	.align 16
	.type	foo, @object
	.size	foo, 16
foo:
	.long	2
	.zero	4
	.quad	__compound_literal.0
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
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
