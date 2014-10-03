	.file	"poker_sort.c"
	.text
	.globl	cmp_cards
	.type	cmp_cards, @function
cmp_cards:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	cmp_cards, .-cmp_cards
	.globl	sort_cards
	.type	sort_cards, @function
sort_cards:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$cmp_cards, %ecx
	movl	$8, %edx
	movl	$5, %esi
	movq	%rax, %rdi
	call	qsort
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	sort_cards, .-sort_cards
	.section	.rodata
.LC0:
	.string	"[%d %c]"
	.text
	.globl	print_cards
	.type	print_cards, @function
print_cards:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L5
.L7:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	4(%rax), %eax
	movsbl	%al, %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	cmpl	$4, -4(%rbp)
	je	.L6
	movl	$32, %edi
	call	putchar
.L6:
	addl	$1, -4(%rbp)
.L5:
	cmpl	$4, -4(%rbp)
	jle	.L7
	movl	$10, %edi
	call	putchar
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	print_cards, .-print_cards
	.globl	parse_card_type
	.type	parse_card_type, @function
parse_card_type:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$83, -4(%rbp)
	jne	.L9
	movl	$0, %eax
	jmp	.L10
.L9:
	cmpb	$72, -4(%rbp)
	jne	.L11
	movl	$1, %eax
	jmp	.L10
.L11:
	cmpb	$67, -4(%rbp)
	jne	.L12
	movl	$2, %eax
	jmp	.L10
.L12:
	cmpb	$68, -4(%rbp)
	jne	.L13
	movl	$3, %eax
	jmp	.L10
.L13:
	movl	$-1, %eax
.L10:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	parse_card_type, .-parse_card_type
	.globl	parse_card_id
	.type	parse_card_id, @function
parse_card_id:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$49, -4(%rbp)
	jle	.L15
	cmpb	$57, -4(%rbp)
	jg	.L15
	movsbl	-4(%rbp), %eax
	subl	$48, %eax
	jmp	.L16
.L15:
	cmpb	$48, -4(%rbp)
	jne	.L17
	movl	$10, %eax
	jmp	.L16
.L17:
	cmpb	$74, -4(%rbp)
	jne	.L18
	movl	$11, %eax
	jmp	.L16
.L18:
	cmpb	$81, -4(%rbp)
	jne	.L19
	movl	$12, %eax
	jmp	.L16
.L19:
	cmpb	$75, -4(%rbp)
	jne	.L20
	movl	$13, %eax
	jmp	.L16
.L20:
	cmpb	$65, -4(%rbp)
	jne	.L21
	movl	$14, %eax
	jmp	.L16
.L21:
	movl	$-1, %eax
.L16:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	parse_card_id, .-parse_card_id
	.globl	parse_stub_type
	.type	parse_stub_type, @function
parse_stub_type:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	addq	$4, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movzbl	4(%rax), %eax
	cmpb	$83, %al
	jne	.L23
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L23
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movzbl	4(%rax), %eax
	cmpb	$83, %al
	jne	.L23
	movq	-24(%rbp), %rax
	addq	$16, %rax
	movzbl	4(%rax), %eax
	cmpb	$83, %al
	jne	.L23
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movzbl	4(%rax), %eax
	cmpb	$83, %al
	jne	.L23
	movq	-24(%rbp), %rax
	addq	$32, %rax
	movzbl	4(%rax), %eax
	cmpb	$83, %al
	jne	.L23
	movl	$0, %eax
	jmp	.L22
.L23:
	movq	-24(%rbp), %rax
	movzbl	4(%rax), %edx
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movzbl	4(%rax), %eax
	cmpb	%al, %dl
	jne	.L25
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movzbl	4(%rax), %edx
	movq	-24(%rbp), %rax
	addq	$16, %rax
	movzbl	4(%rax), %eax
	cmpb	%al, %dl
	jne	.L25
	movq	-24(%rbp), %rax
	addq	$16, %rax
	movzbl	4(%rax), %edx
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movzbl	4(%rax), %eax
	cmpb	%al, %dl
	jne	.L25
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movzbl	4(%rax), %edx
	movq	-24(%rbp), %rax
	addq	$32, %rax
	movzbl	4(%rax), %eax
	cmpb	%al, %dl
	jne	.L25
	movl	$1, %eax
	jmp	.L22
.L25:
	movl	$0, -32(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L26
.L27:
	movl	-32(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	4(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	parse_card_type
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	cltq
	movl	-16(%rbp,%rax,4), %eax
	leal	1(%rax), %edx
	movl	-28(%rbp), %eax
	cltq
	movl	%edx, -16(%rbp,%rax,4)
	addl	$1, -32(%rbp)
.L26:
	cmpl	$4, -32(%rbp)
	jle	.L27
	movl	-16(%rbp), %eax
	cmpl	$4, %eax
	je	.L28
	movl	-12(%rbp), %eax
	cmpl	$4, %eax
	je	.L28
	movl	-8(%rbp), %eax
	cmpl	$4, %eax
	je	.L28
	movl	-4(%rbp), %eax
	cmpl	$4, %eax
	jne	.L29
.L28:
	movl	$2, %eax
	jmp	.L22
.L29:
.L22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	parse_stub_type, .-parse_stub_type
	.globl	cmp_stubs
	.type	cmp_stubs, @function
cmp_stubs:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movl	$-1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	cmp_stubs, .-cmp_stubs
	.globl	sort_stubs
	.type	sort_stubs, @function
sort_stubs:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movslq	%eax, %rsi
	movq	-8(%rbp), %rax
	movl	$cmp_stubs, %ecx
	movl	$44, %edx
	movq	%rax, %rdi
	call	qsort
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	sort_stubs, .-sort_stubs
	.globl	create_stubs
	.type	create_stubs, @function
create_stubs:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	create_stubs, .-create_stubs
	.section	.rodata
.LC1:
	.string	"%d\n"
.LC2:
	.string	"ary %d < %d\n"
.LC3:
	.string	"stub %d < %d\n"
.LC4:
	.string	"%1s"
.LC5:
	.string	"ary_i %d %d\n"
.LC6:
	.string	" "
.LC7:
	.string	"\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$0, -20(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	jmp	.L37
.L43:
	movl	-28(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -16(%rbp)
	movl	$46, %edi
	call	putchar
	leaq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$33, %edi
	call	putchar
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	create_stubs
	movq	%rax, -8(%rbp)
	jmp	.L38
.L42:
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	-16(%rbp), %edx
	addl	$1, %edx
	movl	%edx, (%rax)
	movl	$0, -12(%rbp)
	movl	-24(%rbp), %edx
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L39
.L41:
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rdx, %rax
	addq	$8, %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-28(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	leaq	-29(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-28(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movzbl	-29(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	putchar
	cmpl	$4, -12(%rbp)
	je	.L40
	movl	$.LC6, %edi
	movl	$0, %eax
	call	__isoc99_scanf
.L40:
	addl	$1, -12(%rbp)
.L39:
	cmpl	$4, -12(%rbp)
	jle	.L41
	movl	$10, %edi
	call	putchar
	movl	$.LC7, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	addl	$1, -16(%rbp)
.L38:
	movl	-24(%rbp), %eax
	cmpl	%eax, -16(%rbp)
	jl	.L42
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free
	addl	$1, -20(%rbp)
.L37:
	movl	-28(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L43
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
