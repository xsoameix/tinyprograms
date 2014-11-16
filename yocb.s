	.file	"yocb.c"
	.text
	.globl	ckfree
	.type	ckfree, @function
ckfree:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$0, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	ckfree, .-ckfree
	.type	h_hash, @function
h_hash:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -32(%rbp)
	movq	%rsi, -40(%rbp)
	movl	$2166136261, %ebx
	movq	$0, -16(%rbp)
	jmp	.L3
.L4:
	movq	-32(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -32(%rbp)
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	xorq	%rax, %rbx
	imulq	$16777619, %rbx, %rbx
	addq	$1, -16(%rbp)
.L3:
	movq	-16(%rbp), %rax
	cmpq	-40(%rbp), %rax
	jb	.L4
	movq	%rbx, %rax
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	h_hash, .-h_hash
	.globl	h_bin_pos
	.type	h_bin_pos, @function
h_bin_pos:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-16(%rbp), %rax
	movl	$0, %edx
	divq	%rcx
	movq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	h_bin_pos, .-h_bin_pos
	.globl	h_new_entry
	.type	h_new_entry, @function
h_new_entry:
.LFB5:
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
	movq	%r9, -64(%rbp)
	movl	$56, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 24(%rax)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	-64(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 32(%rax)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	-64(%rbp), %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, (%rdx)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	h_new_entry, .-h_new_entry
	.globl	h_realloc
	.type	h_realloc, @function
h_realloc:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc
	movq	-8(%rbp), %rdx
	movq	%rax, 16(%rdx)
	movq	-16(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	h_realloc, .-h_realloc
	.section	.rodata
	.align 32
	.type	h_primes, @object
	.size	h_primes, 232
h_primes:
	.quad	11
	.quad	19
	.quad	37
	.quad	67
	.quad	131
	.quad	283
	.quad	521
	.quad	1033
	.quad	2053
	.quad	4099
	.quad	8219
	.quad	16427
	.quad	32771
	.quad	65581
	.quad	131101
	.quad	262147
	.quad	524309
	.quad	1048583
	.quad	2097169
	.quad	4194319
	.quad	8388617
	.quad	16777259
	.quad	33554467
	.quad	67108879
	.quad	134217757
	.quad	268435459
	.quad	536870923
	.quad	1073741909
	.quad	0
.LC0:
	.string	"hash table too big"
	.text
	.globl	h_new_capa
	.type	h_new_capa, @function
h_new_capa:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$8, -16(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L12
.L15:
	movq	-16(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jbe	.L13
	movq	-8(%rbp), %rax
	movq	h_primes(,%rax,8), %rax
	jmp	.L16
.L13:
	salq	-16(%rbp)
	addq	$1, -8(%rbp)
.L12:
	cmpq	$28, -8(%rbp)
	jbe	.L15
	movl	$.LC0, %edi
	call	puts
	movl	$0, %edi
	call	exit
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	h_new_capa, .-h_new_capa
	.globl	h_rehash
	.type	h_rehash, @function
h_rehash:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	h_new_capa
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	h_realloc
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L17
.L19:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	h_bin_pos
	movq	%rax, -8(%rbp)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	-8(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 32(%rax)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	-8(%rbp), %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rax, (%rdx)
	movq	-24(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L19
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	h_rehash, .-h_rehash
	.globl	h_add
	.type	h_add, @function
h_add:
.LFB9:
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
	movq	%r9, -64(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	cmpq	%rax, %rcx
	jbe	.L21
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	h_rehash
	movq	-56(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	h_bin_pos
	movq	%rax, -64(%rbp)
.L21:
	movq	-64(%rbp), %r8
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%r8, %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	h_new_entry
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	testq	%rax, %rax
	je	.L22
	movq	-24(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 40(%rax)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 48(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 48(%rax)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 32(%rax)
	jmp	.L23
.L22:
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 32(%rax)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 48(%rax)
	movq	-8(%rbp), %rax
	movq	48(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 40(%rax)
.L23:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	leaq	1(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 8(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	h_add, .-h_add
	.globl	h_eq
	.type	h_eq, @function
h_eq:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rax
	cmpq	-24(%rbp), %rax
	je	.L25
	movq	-16(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jne	.L26
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcmp
	testl	%eax, %eax
	je	.L26
.L25:
	movl	$1, %eax
	jmp	.L27
.L26:
	movl	$0, %eax
.L27:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	h_eq, .-h_eq
	.globl	h_hit
	.type	h_hit, @function
h_hit:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L30
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-32(%rbp), %rax
	jne	.L31
	movq	-8(%rbp), %rax
	movq	8(%rax), %rsi
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	-24(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	%rax, %rdi
	call	h_eq
	testl	%eax, %eax
	je	.L30
.L31:
	movl	$1, %eax
	jmp	.L32
.L30:
	movl	$0, %eax
.L32:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	h_hit, .-h_hit
	.globl	h_find
	.type	h_find, @function
h_find:
.LFB12:
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
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	-56(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	h_hit
	testl	%eax, %eax
	je	.L35
	jmp	.L36
.L37:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -8(%rbp)
.L36:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rax, %rdi
	call	h_hit
	testl	%eax, %eax
	jne	.L37
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -8(%rbp)
.L35:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	h_find, .-h_find
	.globl	h_lookup
	.type	h_lookup, @function
h_lookup:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movq	%r8, -72(%rbp)
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	h_hash
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	h_bin_pos
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rcx
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rax
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	h_find
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %r9
	movq	-24(%rbp), %r8
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rdi
	movq	-8(%rbp), %rax
	movq	%rax, (%rsp)
	movq	-72(%rbp), %rax
	call	*%rax
	cmpq	$0, -8(%rbp)
	setne	%al
	movzbl	%al, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	h_lookup, .-h_lookup
	.globl	h_insert_cb
	.type	h_insert_cb, @function
h_insert_cb:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	cmpq	$0, 16(%rbp)
	jne	.L42
	movq	-48(%rbp), %r8
	movq	-40(%rbp), %rdi
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movq	%r8, %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	h_add
	jmp	.L41
.L42:
	movq	16(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 24(%rax)
.L41:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	h_insert_cb, .-h_insert_cb
	.globl	h_get_cb
	.type	h_get_cb, @function
h_get_cb:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	cmpq	$0, 16(%rbp)
	je	.L44
	cmpq	$0, -32(%rbp)
	je	.L44
	movq	16(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, (%rax)
.L44:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	h_get_cb, .-h_get_cb
	.globl	h_insert
	.type	h_insert, @function
h_insert:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movl	$h_insert_cb, %r8d
	movq	%rax, %rdi
	call	h_lookup
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	h_insert, .-h_insert
	.globl	h_get
	.type	h_get, @function
h_get:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movl	$h_get_cb, %r8d
	movq	%rax, %rdi
	call	h_lookup
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	h_get, .-h_get
	.globl	h_contains
	.type	h_contains, @function
h_contains:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movl	$h_get_cb, %r8d
	movl	$0, %ecx
	movq	%rax, %rdi
	call	h_lookup
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	h_contains, .-h_contains
	.globl	h_merge
	.type	h_merge, @function
h_merge:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L53
.L54:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	h_insert
	movq	-8(%rbp), %rax
	movq	48(%rax), %rax
	movq	%rax, -8(%rbp)
.L53:
	cmpq	$0, -8(%rbp)
	jne	.L54
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	h_merge, .-h_merge
	.globl	h_init_with_capa
	.type	h_init_with_capa, @function
h_init_with_capa:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	h_new_capa
	movq	%rax, -24(%rbp)
	movl	$40, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	h_init_with_capa, .-h_init_with_capa
	.globl	h_init
	.type	h_init, @function
h_init:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %edi
	call	h_init_with_capa
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	h_init, .-h_init
	.globl	h_clear
	.type	h_clear, @function
h_clear:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	$0, -24(%rbp)
	jmp	.L60
.L63:
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	-24(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L61
.L62:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
.L61:
	cmpq	$0, -16(%rbp)
	jne	.L62
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	-24(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	$0, (%rax)
	addq	$1, -24(%rbp)
.L60:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-24(%rbp), %rax
	ja	.L63
	movq	-40(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-40(%rbp), %rax
	movq	$0, 24(%rax)
	movq	-40(%rbp), %rax
	movq	$0, 32(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	h_clear, .-h_clear
	.globl	h_free
	.type	h_free, @function
h_free:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	h_clear
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	ckfree
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	h_free, .-h_free
	.data
	.align 32
	.type	trans, @object
	.size	trans, 2048
trans:
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	2
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	4
	.byte	3
	.byte	3
	.byte	5
	.byte	6
	.byte	6
	.byte	6
	.byte	7
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.text
	.type	utf8_len, @function
utf8_len:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -8(%rbp)
.L70:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	cltq
	movq	-8(%rbp), %rdx
	salq	$8, %rdx
	addq	%rdx, %rax
	addq	$trans, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	%rax, -8(%rbp)
	addq	$1, -24(%rbp)
	addq	$1, -16(%rbp)
	movq	-8(%rbp), %rax
	cmpq	$-2, %rax
	je	.L67
	cmpq	$-1, %rax
	je	.L68
	jmp	.L70
.L67:
	movq	-16(%rbp), %rax
	jmp	.L69
.L68:
	movl	$0, %eax
.L69:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	utf8_len, .-utf8_len
	.type	utf8_code, @function
utf8_code:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, -12(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -8(%rbp)
	cmpq	$1, -8(%rbp)
	jbe	.L72
	subq	$1, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$6, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	andl	%eax, -12(%rbp)
	jmp	.L73
.L74:
	addq	$1, -24(%rbp)
	sall	$6, -12(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$63, %eax
	orl	%eax, -12(%rbp)
.L73:
	movq	-8(%rbp), %rax
	leaq	-1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	testq	%rax, %rax
	jne	.L74
.L72:
	movl	-12(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	utf8_code, .-utf8_code
	.section	.rodata
.LC1:
	.string	"should input 1 file"
.LC2:
	.string	"r"
.LC3:
	.string	"no %s file\n"
	.text
	.globl	file_open
	.type	file_open, @function
file_open:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$1, -20(%rbp)
	je	.L77
	movl	$.LC1, %edi
	call	puts
	movl	$0, %edi
	call	exit
.L77:
	movq	-32(%rbp), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	fopen
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L78
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
.L78:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	file_open, .-file_open
	.section	.rodata
	.align 8
.LC4:
	.string	"alloc memory error for file %s\n"
.LC5:
	.string	"reading error for file %s\n"
	.text
	.globl	file_read
	.type	file_read, @function
file_read:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%rcx, -80(%rbp)
	movq	-64(%rbp), %rdx
	movl	-52(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	file_open
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	ftell
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	rewind
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L81
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
.L81:
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	cmpq	-32(%rbp), %rax
	je	.L82
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
.L82:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	movq	-80(%rbp), %rcx
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rsi
	movq	-64(%rbp), %rdi
	movq	-72(%rbp), %rax
	call	*%rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L83
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
.L83:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	file_read, .-file_read
	.globl	scan_is
	.type	scan_is, @function
scan_is:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	$0, -16(%rbp)
.L93:
	movq	-16(%rbp), %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L86
	salq	-16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	-20(%rbp), %eax
	jb	.L87
	movl	$1, %eax
	jmp	.L88
.L87:
	movl	$2, %eax
.L88:
	addq	%rax, -16(%rbp)
	jmp	.L93
.L86:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movl	(%rax), %eax
	cmpl	-20(%rbp), %eax
	ja	.L90
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	addq	$4, %rax
	movl	(%rax), %eax
	cmpl	-20(%rbp), %eax
	jb	.L90
	movl	$1, %eax
	jmp	.L91
.L90:
	movl	$0, %eax
.L91:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	scan_is, .-scan_is
	.section	.rodata
.LC6:
	.string	"read end of file %zu\n"
	.text
	.globl	scan_char
	.type	scan_char, @function
scan_char:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-64(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jb	.L95
	movq	-64(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L96
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
.L96:
	movq	-64(%rbp), %rax
	movq	$1, 32(%rax)
	movq	-56(%rbp), %rax
	movq	$0, (%rax)
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
	jmp	.L94
.L95:
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_code
	movl	%eax, -44(%rbp)
	movq	-56(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rax
	movl	-44(%rbp), %edx
	movl	%edx, 8(%rax)
	movq	-56(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
.L94:
	movq	-56(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	scan_char, .-scan_char
	.section	.rodata
.LC7:
	.string	"not allowed char %u\n"
	.text
	.globl	scan_perror
	.type	scan_perror, @function
scan_perror:
.LFB30:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE30:
	.size	scan_perror, .-scan_perror
	.data
	.align 4
	.type	__compound_literal.0, @object
	.size	__compound_literal.0, 8
__compound_literal.0:
	.long	97
	.long	122
	.align 4
	.type	__compound_literal.1, @object
	.size	__compound_literal.1, 8
__compound_literal.1:
	.long	65
	.long	90
	.align 4
	.type	__compound_literal.2, @object
	.size	__compound_literal.2, 8
__compound_literal.2:
	.long	95
	.long	95
	.align 32
	.type	ccall, @object
	.size	ccall, 80
ccall:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.0
	.long	0
	.zero	4
	.quad	__compound_literal.1
	.long	0
	.zero	4
	.quad	__compound_literal.2
	.align 4
	.type	__compound_literal.3, @object
	.size	__compound_literal.3, 8
__compound_literal.3:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.4, @object
	.size	__compound_literal.4, 8
__compound_literal.4:
	.long	97
	.long	114
	.align 4
	.type	__compound_literal.5, @object
	.size	__compound_literal.5, 8
__compound_literal.5:
	.long	116
	.long	122
	.align 4
	.type	__compound_literal.6, @object
	.size	__compound_literal.6, 8
__compound_literal.6:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.7, @object
	.size	__compound_literal.7, 8
__compound_literal.7:
	.long	65
	.long	90
	.align 32
	.type	cdid, @object
	.size	cdid, 144
cdid:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	114
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.3
	.long	0
	.zero	4
	.quad	__compound_literal.4
	.long	0
	.zero	4
	.quad	__compound_literal.5
	.long	0
	.zero	4
	.quad	__compound_literal.6
	.long	0
	.zero	4
	.quad	__compound_literal.7
	.align 4
	.type	__compound_literal.8, @object
	.size	__compound_literal.8, 8
__compound_literal.8:
	.long	102
	.long	113
	.align 4
	.type	__compound_literal.9, @object
	.size	__compound_literal.9, 8
__compound_literal.9:
	.long	115
	.long	122
	.align 4
	.type	__compound_literal.10, @object
	.size	__compound_literal.10, 8
__compound_literal.10:
	.long	65
	.long	90
	.align 4
	.type	__compound_literal.11, @object
	.size	__compound_literal.11, 8
__compound_literal.11:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.12, @object
	.size	__compound_literal.12, 8
__compound_literal.12:
	.long	97
	.long	98
	.align 4
	.type	__compound_literal.13, @object
	.size	__compound_literal.13, 8
__compound_literal.13:
	.long	100
	.long	100
	.align 32
	.type	cmethod, @object
	.size	cmethod, 176
cmethod:
	.long	100
	.zero	4
	.quad	0
	.long	95
	.zero	4
	.quad	0
	.long	113
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	98
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.8
	.long	0
	.zero	4
	.quad	__compound_literal.9
	.long	0
	.zero	4
	.quad	__compound_literal.10
	.long	0
	.zero	4
	.quad	__compound_literal.11
	.long	0
	.zero	4
	.quad	__compound_literal.12
	.long	0
	.zero	4
	.quad	__compound_literal.13
	.align 4
	.type	__compound_literal.14, @object
	.size	__compound_literal.14, 8
__compound_literal.14:
	.long	110
	.long	114
	.align 4
	.type	__compound_literal.15, @object
	.size	__compound_literal.15, 8
__compound_literal.15:
	.long	116
	.long	122
	.align 4
	.type	__compound_literal.16, @object
	.size	__compound_literal.16, 8
__compound_literal.16:
	.long	65
	.long	90
	.align 4
	.type	__compound_literal.17, @object
	.size	__compound_literal.17, 8
__compound_literal.17:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.18, @object
	.size	__compound_literal.18, 8
__compound_literal.18:
	.long	97
	.long	98
	.align 4
	.type	__compound_literal.19, @object
	.size	__compound_literal.19, 8
__compound_literal.19:
	.long	100
	.long	108
	.align 32
	.type	did_head, @object
	.size	did_head, 176
did_head:
	.long	108
	.zero	4
	.quad	0
	.long	95
	.zero	4
	.quad	0
	.long	114
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	98
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.14
	.long	0
	.zero	4
	.quad	__compound_literal.15
	.long	0
	.zero	4
	.quad	__compound_literal.16
	.long	0
	.zero	4
	.quad	__compound_literal.17
	.long	0
	.zero	4
	.quad	__compound_literal.18
	.long	0
	.zero	4
	.quad	__compound_literal.19
	.align 4
	.type	__compound_literal.20, @object
	.size	__compound_literal.20, 8
__compound_literal.20:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.21, @object
	.size	__compound_literal.21, 8
__compound_literal.21:
	.long	65
	.long	90
	.align 4
	.type	__compound_literal.22, @object
	.size	__compound_literal.22, 8
__compound_literal.22:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.23, @object
	.size	__compound_literal.23, 8
__compound_literal.23:
	.long	97
	.long	122
	.align 32
	.type	did_tail, @object
	.size	did_tail, 112
did_tail:
	.long	90
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	95
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.20
	.long	0
	.zero	4
	.quad	__compound_literal.21
	.long	0
	.zero	4
	.quad	__compound_literal.22
	.long	0
	.zero	4
	.quad	__compound_literal.23
	.align 4
	.type	__compound_literal.24, @object
	.size	__compound_literal.24, 8
__compound_literal.24:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.25, @object
	.size	__compound_literal.25, 8
__compound_literal.25:
	.long	97
	.long	107
	.align 4
	.type	__compound_literal.26, @object
	.size	__compound_literal.26, 8
__compound_literal.26:
	.long	109
	.long	122
	.align 4
	.type	__compound_literal.27, @object
	.size	__compound_literal.27, 8
__compound_literal.27:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.28, @object
	.size	__compound_literal.28, 8
__compound_literal.28:
	.long	65
	.long	90
	.align 32
	.type	dnot_l, @object
	.size	dnot_l, 144
dnot_l:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	107
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.24
	.long	0
	.zero	4
	.quad	__compound_literal.25
	.long	0
	.zero	4
	.quad	__compound_literal.26
	.long	0
	.zero	4
	.quad	__compound_literal.27
	.long	0
	.zero	4
	.quad	__compound_literal.28
	.align 4
	.type	__compound_literal.29, @object
	.size	__compound_literal.29, 8
__compound_literal.29:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.30, @object
	.size	__compound_literal.30, 8
__compound_literal.30:
	.long	97
	.long	96
	.align 4
	.type	__compound_literal.31, @object
	.size	__compound_literal.31, 8
__compound_literal.31:
	.long	98
	.long	122
	.align 4
	.type	__compound_literal.32, @object
	.size	__compound_literal.32, 8
__compound_literal.32:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.33, @object
	.size	__compound_literal.33, 8
__compound_literal.33:
	.long	65
	.long	90
	.align 32
	.type	dnot_a, @object
	.size	dnot_a, 144
dnot_a:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	96
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.29
	.long	0
	.zero	4
	.quad	__compound_literal.30
	.long	0
	.zero	4
	.quad	__compound_literal.31
	.long	0
	.zero	4
	.quad	__compound_literal.32
	.long	0
	.zero	4
	.quad	__compound_literal.33
	.align 4
	.type	__compound_literal.34, @object
	.size	__compound_literal.34, 8
__compound_literal.34:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.35, @object
	.size	__compound_literal.35, 8
__compound_literal.35:
	.long	97
	.long	114
	.align 4
	.type	__compound_literal.36, @object
	.size	__compound_literal.36, 8
__compound_literal.36:
	.long	116
	.long	122
	.align 4
	.type	__compound_literal.37, @object
	.size	__compound_literal.37, 8
__compound_literal.37:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.38, @object
	.size	__compound_literal.38, 8
__compound_literal.38:
	.long	65
	.long	90
	.align 32
	.type	dnot_s, @object
	.size	dnot_s, 144
dnot_s:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	114
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.34
	.long	0
	.zero	4
	.quad	__compound_literal.35
	.long	0
	.zero	4
	.quad	__compound_literal.36
	.long	0
	.zero	4
	.quad	__compound_literal.37
	.long	0
	.zero	4
	.quad	__compound_literal.38
	.align 4
	.type	__compound_literal.39, @object
	.size	__compound_literal.39, 8
__compound_literal.39:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.40, @object
	.size	__compound_literal.40, 8
__compound_literal.40:
	.long	97
	.long	100
	.align 4
	.type	__compound_literal.41, @object
	.size	__compound_literal.41, 8
__compound_literal.41:
	.long	102
	.long	122
	.align 4
	.type	__compound_literal.42, @object
	.size	__compound_literal.42, 8
__compound_literal.42:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.43, @object
	.size	__compound_literal.43, 8
__compound_literal.43:
	.long	65
	.long	90
	.align 32
	.type	dnot_e, @object
	.size	dnot_e, 144
dnot_e:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	100
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.39
	.long	0
	.zero	4
	.quad	__compound_literal.40
	.long	0
	.zero	4
	.quad	__compound_literal.41
	.long	0
	.zero	4
	.quad	__compound_literal.42
	.long	0
	.zero	4
	.quad	__compound_literal.43
	.align 4
	.type	__compound_literal.44, @object
	.size	__compound_literal.44, 8
__compound_literal.44:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.45, @object
	.size	__compound_literal.45, 8
__compound_literal.45:
	.long	97
	.long	115
	.align 4
	.type	__compound_literal.46, @object
	.size	__compound_literal.46, 8
__compound_literal.46:
	.long	117
	.long	122
	.align 4
	.type	__compound_literal.47, @object
	.size	__compound_literal.47, 8
__compound_literal.47:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.48, @object
	.size	__compound_literal.48, 8
__compound_literal.48:
	.long	65
	.long	90
	.align 32
	.type	dnot_t, @object
	.size	dnot_t, 144
dnot_t:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	115
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.44
	.long	0
	.zero	4
	.quad	__compound_literal.45
	.long	0
	.zero	4
	.quad	__compound_literal.46
	.long	0
	.zero	4
	.quad	__compound_literal.47
	.long	0
	.zero	4
	.quad	__compound_literal.48
	.align 4
	.type	__compound_literal.49, @object
	.size	__compound_literal.49, 8
__compound_literal.49:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.50, @object
	.size	__compound_literal.50, 8
__compound_literal.50:
	.long	97
	.long	103
	.align 4
	.type	__compound_literal.51, @object
	.size	__compound_literal.51, 8
__compound_literal.51:
	.long	105
	.long	122
	.align 4
	.type	__compound_literal.52, @object
	.size	__compound_literal.52, 8
__compound_literal.52:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.53, @object
	.size	__compound_literal.53, 8
__compound_literal.53:
	.long	65
	.long	90
	.align 32
	.type	dnot_h, @object
	.size	dnot_h, 144
dnot_h:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	103
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.49
	.long	0
	.zero	4
	.quad	__compound_literal.50
	.long	0
	.zero	4
	.quad	__compound_literal.51
	.long	0
	.zero	4
	.quad	__compound_literal.52
	.long	0
	.zero	4
	.quad	__compound_literal.53
	.align 4
	.type	__compound_literal.54, @object
	.size	__compound_literal.54, 8
__compound_literal.54:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.55, @object
	.size	__compound_literal.55, 8
__compound_literal.55:
	.long	97
	.long	110
	.align 4
	.type	__compound_literal.56, @object
	.size	__compound_literal.56, 8
__compound_literal.56:
	.long	112
	.long	122
	.align 4
	.type	__compound_literal.57, @object
	.size	__compound_literal.57, 8
__compound_literal.57:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.58, @object
	.size	__compound_literal.58, 8
__compound_literal.58:
	.long	65
	.long	90
	.align 32
	.type	dnot_o, @object
	.size	dnot_o, 144
dnot_o:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	110
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.54
	.long	0
	.zero	4
	.quad	__compound_literal.55
	.long	0
	.zero	4
	.quad	__compound_literal.56
	.long	0
	.zero	4
	.quad	__compound_literal.57
	.long	0
	.zero	4
	.quad	__compound_literal.58
	.align 4
	.type	__compound_literal.59, @object
	.size	__compound_literal.59, 8
__compound_literal.59:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.60, @object
	.size	__compound_literal.60, 8
__compound_literal.60:
	.long	97
	.long	99
	.align 4
	.type	__compound_literal.61, @object
	.size	__compound_literal.61, 8
__compound_literal.61:
	.long	101
	.long	122
	.align 4
	.type	__compound_literal.62, @object
	.size	__compound_literal.62, 8
__compound_literal.62:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.63, @object
	.size	__compound_literal.63, 8
__compound_literal.63:
	.long	65
	.long	90
	.align 32
	.type	dnot_d, @object
	.size	dnot_d, 144
dnot_d:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	99
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.59
	.long	0
	.zero	4
	.quad	__compound_literal.60
	.long	0
	.zero	4
	.quad	__compound_literal.61
	.long	0
	.zero	4
	.quad	__compound_literal.62
	.long	0
	.zero	4
	.quad	__compound_literal.63
	.align 4
	.type	__compound_literal.64, @object
	.size	__compound_literal.64, 8
__compound_literal.64:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.65, @object
	.size	__compound_literal.65, 8
__compound_literal.65:
	.long	97
	.long	113
	.align 4
	.type	__compound_literal.66, @object
	.size	__compound_literal.66, 8
__compound_literal.66:
	.long	115
	.long	122
	.align 4
	.type	__compound_literal.67, @object
	.size	__compound_literal.67, 8
__compound_literal.67:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.68, @object
	.size	__compound_literal.68, 8
__compound_literal.68:
	.long	65
	.long	90
	.align 32
	.type	dnot_r, @object
	.size	dnot_r, 144
dnot_r:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	113
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.64
	.long	0
	.zero	4
	.quad	__compound_literal.65
	.long	0
	.zero	4
	.quad	__compound_literal.66
	.long	0
	.zero	4
	.quad	__compound_literal.67
	.long	0
	.zero	4
	.quad	__compound_literal.68
	.align 4
	.type	__compound_literal.69, @object
	.size	__compound_literal.69, 8
__compound_literal.69:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.70, @object
	.size	__compound_literal.70, 8
__compound_literal.70:
	.long	97
	.long	116
	.align 4
	.type	__compound_literal.71, @object
	.size	__compound_literal.71, 8
__compound_literal.71:
	.long	118
	.long	122
	.align 4
	.type	__compound_literal.72, @object
	.size	__compound_literal.72, 8
__compound_literal.72:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.73, @object
	.size	__compound_literal.73, 8
__compound_literal.73:
	.long	65
	.long	90
	.align 32
	.type	dnot_u, @object
	.size	dnot_u, 144
dnot_u:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	116
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.69
	.long	0
	.zero	4
	.quad	__compound_literal.70
	.long	0
	.zero	4
	.quad	__compound_literal.71
	.long	0
	.zero	4
	.quad	__compound_literal.72
	.long	0
	.zero	4
	.quad	__compound_literal.73
	.align 4
	.type	__compound_literal.74, @object
	.size	__compound_literal.74, 8
__compound_literal.74:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.75, @object
	.size	__compound_literal.75, 8
__compound_literal.75:
	.long	97
	.long	98
	.align 4
	.type	__compound_literal.76, @object
	.size	__compound_literal.76, 8
__compound_literal.76:
	.long	100
	.long	122
	.align 4
	.type	__compound_literal.77, @object
	.size	__compound_literal.77, 8
__compound_literal.77:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.78, @object
	.size	__compound_literal.78, 8
__compound_literal.78:
	.long	65
	.long	90
	.align 32
	.type	dnot_c, @object
	.size	dnot_c, 144
dnot_c:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	98
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.74
	.long	0
	.zero	4
	.quad	__compound_literal.75
	.long	0
	.zero	4
	.quad	__compound_literal.76
	.long	0
	.zero	4
	.quad	__compound_literal.77
	.long	0
	.zero	4
	.quad	__compound_literal.78
	.align 4
	.type	__compound_literal.79, @object
	.size	__compound_literal.79, 8
__compound_literal.79:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.80, @object
	.size	__compound_literal.80, 8
__compound_literal.80:
	.long	97
	.long	109
	.align 4
	.type	__compound_literal.81, @object
	.size	__compound_literal.81, 8
__compound_literal.81:
	.long	111
	.long	122
	.align 4
	.type	__compound_literal.82, @object
	.size	__compound_literal.82, 8
__compound_literal.82:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.83, @object
	.size	__compound_literal.83, 8
__compound_literal.83:
	.long	65
	.long	90
	.align 32
	.type	dnot_n, @object
	.size	dnot_n, 144
dnot_n:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	109
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.79
	.long	0
	.zero	4
	.quad	__compound_literal.80
	.long	0
	.zero	4
	.quad	__compound_literal.81
	.long	0
	.zero	4
	.quad	__compound_literal.82
	.long	0
	.zero	4
	.quad	__compound_literal.83
	.align 4
	.type	__compound_literal.84, @object
	.size	__compound_literal.84, 8
__compound_literal.84:
	.long	102
	.long	115
	.align 4
	.type	__compound_literal.85, @object
	.size	__compound_literal.85, 8
__compound_literal.85:
	.long	118
	.long	122
	.align 4
	.type	__compound_literal.86, @object
	.size	__compound_literal.86, 8
__compound_literal.86:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.87, @object
	.size	__compound_literal.87, 8
__compound_literal.87:
	.long	65
	.long	90
	.align 4
	.type	__compound_literal.88, @object
	.size	__compound_literal.88, 8
__compound_literal.88:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.89, @object
	.size	__compound_literal.89, 8
__compound_literal.89:
	.long	97
	.long	100
	.align 32
	.type	dcself1, @object
	.size	dcself1, 176
dcself1:
	.long	100
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	116
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	95
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.84
	.long	0
	.zero	4
	.quad	__compound_literal.85
	.long	0
	.zero	4
	.quad	__compound_literal.86
	.long	0
	.zero	4
	.quad	__compound_literal.87
	.long	0
	.zero	4
	.quad	__compound_literal.88
	.long	0
	.zero	4
	.quad	__compound_literal.89
	.align 4
	.type	__compound_literal.90, @object
	.size	__compound_literal.90, 8
__compound_literal.90:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.91, @object
	.size	__compound_literal.91, 8
__compound_literal.91:
	.long	97
	.long	101
	.align 4
	.type	__compound_literal.92, @object
	.size	__compound_literal.92, 8
__compound_literal.92:
	.long	103
	.long	122
	.align 4
	.type	__compound_literal.93, @object
	.size	__compound_literal.93, 8
__compound_literal.93:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.94, @object
	.size	__compound_literal.94, 8
__compound_literal.94:
	.long	65
	.long	90
	.align 32
	.type	dnot_f, @object
	.size	dnot_f, 144
dnot_f:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	101
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.90
	.long	0
	.zero	4
	.quad	__compound_literal.91
	.long	0
	.zero	4
	.quad	__compound_literal.92
	.long	0
	.zero	4
	.quad	__compound_literal.93
	.long	0
	.zero	4
	.quad	__compound_literal.94
	.align 4
	.type	__compound_literal.95, @object
	.size	__compound_literal.95, 8
__compound_literal.95:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.96, @object
	.size	__compound_literal.96, 8
__compound_literal.96:
	.long	97
	.long	111
	.align 4
	.type	__compound_literal.97, @object
	.size	__compound_literal.97, 8
__compound_literal.97:
	.long	113
	.long	122
	.align 4
	.type	__compound_literal.98, @object
	.size	__compound_literal.98, 8
__compound_literal.98:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.99, @object
	.size	__compound_literal.99, 8
__compound_literal.99:
	.long	65
	.long	90
	.align 32
	.type	dnot_p, @object
	.size	dnot_p, 144
dnot_p:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	111
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.95
	.long	0
	.zero	4
	.quad	__compound_literal.96
	.long	0
	.zero	4
	.quad	__compound_literal.97
	.long	0
	.zero	4
	.quad	__compound_literal.98
	.long	0
	.zero	4
	.quad	__compound_literal.99
	.align 4
	.type	__compound_literal.100, @object
	.size	__compound_literal.100, 8
__compound_literal.100:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.101, @object
	.size	__compound_literal.101, 8
__compound_literal.101:
	.long	97
	.long	112
	.align 4
	.type	__compound_literal.102, @object
	.size	__compound_literal.102, 8
__compound_literal.102:
	.long	114
	.long	122
	.align 4
	.type	__compound_literal.103, @object
	.size	__compound_literal.103, 8
__compound_literal.103:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.104, @object
	.size	__compound_literal.104, 8
__compound_literal.104:
	.long	65
	.long	90
	.align 32
	.type	dnot_q, @object
	.size	dnot_q, 144
dnot_q:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	112
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.100
	.long	0
	.zero	4
	.quad	__compound_literal.101
	.long	0
	.zero	4
	.quad	__compound_literal.102
	.long	0
	.zero	4
	.quad	__compound_literal.103
	.long	0
	.zero	4
	.quad	__compound_literal.104
	.align 4
	.type	__compound_literal.105, @object
	.size	__compound_literal.105, 8
__compound_literal.105:
	.long	95
	.long	95
	.align 4
	.type	__compound_literal.106, @object
	.size	__compound_literal.106, 8
__compound_literal.106:
	.long	97
	.long	104
	.align 4
	.type	__compound_literal.107, @object
	.size	__compound_literal.107, 8
__compound_literal.107:
	.long	106
	.long	122
	.align 4
	.type	__compound_literal.108, @object
	.size	__compound_literal.108, 8
__compound_literal.108:
	.long	48
	.long	57
	.align 4
	.type	__compound_literal.109, @object
	.size	__compound_literal.109, 8
__compound_literal.109:
	.long	65
	.long	90
	.align 32
	.type	dnot_i, @object
	.size	dnot_i, 144
dnot_i:
	.long	95
	.zero	4
	.quad	0
	.long	90
	.zero	4
	.quad	0
	.long	104
	.zero	4
	.quad	0
	.long	57
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.105
	.long	0
	.zero	4
	.quad	__compound_literal.106
	.long	0
	.zero	4
	.quad	__compound_literal.107
	.long	0
	.zero	4
	.quad	__compound_literal.108
	.long	0
	.zero	4
	.quad	__compound_literal.109
	.align 4
	.type	__compound_literal.110, @object
	.size	__compound_literal.110, 8
__compound_literal.110:
	.long	32
	.long	32
	.align 4
	.type	__compound_literal.111, @object
	.size	__compound_literal.111, 8
__compound_literal.111:
	.long	10
	.long	10
	.align 4
	.type	__compound_literal.112, @object
	.size	__compound_literal.112, 8
__compound_literal.112:
	.long	13
	.long	13
	.align 32
	.type	dterm1, @object
	.size	dterm1, 80
dterm1:
	.long	13
	.zero	4
	.quad	0
	.long	10
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.quad	__compound_literal.110
	.long	0
	.zero	4
	.quad	__compound_literal.111
	.long	0
	.zero	4
	.quad	__compound_literal.112
	.align 4
	.type	__compound_literal.113, @object
	.size	__compound_literal.113, 8
__compound_literal.113:
	.long	58
	.long	58
	.align 16
	.type	__compound_literal.114, @object
	.size	__compound_literal.114, 16
__compound_literal.114:
	.long	0
	.zero	4
	.quad	__compound_literal.113
	.align 4
	.type	__compound_literal.115, @object
	.size	__compound_literal.115, 8
__compound_literal.115:
	.long	64
	.long	64
	.align 16
	.type	__compound_literal.116, @object
	.size	__compound_literal.116, 16
__compound_literal.116:
	.long	0
	.zero	4
	.quad	__compound_literal.115
	.align 4
	.type	__compound_literal.117, @object
	.size	__compound_literal.117, 8
__compound_literal.117:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.118, @object
	.size	__compound_literal.118, 16
__compound_literal.118:
	.long	0
	.zero	4
	.quad	__compound_literal.117
	.align 4
	.type	__compound_literal.119, @object
	.size	__compound_literal.119, 8
__compound_literal.119:
	.long	40
	.long	40
	.align 16
	.type	__compound_literal.120, @object
	.size	__compound_literal.120, 16
__compound_literal.120:
	.long	0
	.zero	4
	.quad	__compound_literal.119
	.align 4
	.type	__compound_literal.121, @object
	.size	__compound_literal.121, 8
__compound_literal.121:
	.long	41
	.long	41
	.align 16
	.type	__compound_literal.122, @object
	.size	__compound_literal.122, 16
__compound_literal.122:
	.long	0
	.zero	4
	.quad	__compound_literal.121
	.align 4
	.type	__compound_literal.123, @object
	.size	__compound_literal.123, 8
__compound_literal.123:
	.long	123
	.long	123
	.align 16
	.type	__compound_literal.124, @object
	.size	__compound_literal.124, 16
__compound_literal.124:
	.long	0
	.zero	4
	.quad	__compound_literal.123
	.align 4
	.type	__compound_literal.125, @object
	.size	__compound_literal.125, 8
__compound_literal.125:
	.long	125
	.long	125
	.align 16
	.type	__compound_literal.126, @object
	.size	__compound_literal.126, 16
__compound_literal.126:
	.long	0
	.zero	4
	.quad	__compound_literal.125
	.align 4
	.type	__compound_literal.127, @object
	.size	__compound_literal.127, 8
__compound_literal.127:
	.long	34
	.long	34
	.align 16
	.type	__compound_literal.128, @object
	.size	__compound_literal.128, 16
__compound_literal.128:
	.long	0
	.zero	4
	.quad	__compound_literal.127
	.align 4
	.type	__compound_literal.129, @object
	.size	__compound_literal.129, 8
__compound_literal.129:
	.long	92
	.long	92
	.align 16
	.type	__compound_literal.130, @object
	.size	__compound_literal.130, 16
__compound_literal.130:
	.long	0
	.zero	4
	.quad	__compound_literal.129
	.align 4
	.type	__compound_literal.131, @object
	.size	__compound_literal.131, 8
__compound_literal.131:
	.long	47
	.long	47
	.align 16
	.type	__compound_literal.132, @object
	.size	__compound_literal.132, 16
__compound_literal.132:
	.long	0
	.zero	4
	.quad	__compound_literal.131
	.align 4
	.type	__compound_literal.133, @object
	.size	__compound_literal.133, 8
__compound_literal.133:
	.long	42
	.long	42
	.align 16
	.type	__compound_literal.134, @object
	.size	__compound_literal.134, 16
__compound_literal.134:
	.long	0
	.zero	4
	.quad	__compound_literal.133
	.align 4
	.type	__compound_literal.135, @object
	.size	__compound_literal.135, 8
__compound_literal.135:
	.long	35
	.long	35
	.align 16
	.type	__compound_literal.136, @object
	.size	__compound_literal.136, 16
__compound_literal.136:
	.long	0
	.zero	4
	.quad	__compound_literal.135
	.align 4
	.type	__compound_literal.137, @object
	.size	__compound_literal.137, 8
__compound_literal.137:
	.long	59
	.long	59
	.align 16
	.type	__compound_literal.138, @object
	.size	__compound_literal.138, 16
__compound_literal.138:
	.long	0
	.zero	4
	.quad	__compound_literal.137
	.align 4
	.type	__compound_literal.139, @object
	.size	__compound_literal.139, 8
__compound_literal.139:
	.long	32
	.long	32
	.align 16
	.type	__compound_literal.140, @object
	.size	__compound_literal.140, 16
__compound_literal.140:
	.long	0
	.zero	4
	.quad	__compound_literal.139
	.align 4
	.type	__compound_literal.141, @object
	.size	__compound_literal.141, 8
__compound_literal.141:
	.long	10
	.long	10
	.align 16
	.type	__compound_literal.142, @object
	.size	__compound_literal.142, 16
__compound_literal.142:
	.long	0
	.zero	4
	.quad	__compound_literal.141
	.align 4
	.type	__compound_literal.143, @object
	.size	__compound_literal.143, 8
__compound_literal.143:
	.long	183
	.long	183
	.align 16
	.type	__compound_literal.144, @object
	.size	__compound_literal.144, 16
__compound_literal.144:
	.long	0
	.zero	4
	.quad	__compound_literal.143
	.align 4
	.type	__compound_literal.145, @object
	.size	__compound_literal.145, 8
__compound_literal.145:
	.long	718
	.long	718
	.align 16
	.type	__compound_literal.146, @object
	.size	__compound_literal.146, 16
__compound_literal.146:
	.long	0
	.zero	4
	.quad	__compound_literal.145
	.align 32
	.type	__compound_literal.147, @object
	.size	__compound_literal.147, 304
__compound_literal.147:
	.quad	cdid
	.long	39
	.zero	4
	.quad	__compound_literal.114
	.long	21
	.zero	4
	.quad	__compound_literal.116
	.long	23
	.zero	4
	.quad	__compound_literal.118
	.long	25
	.zero	4
	.quad	__compound_literal.120
	.long	40
	.zero	4
	.quad	__compound_literal.122
	.long	41
	.zero	4
	.quad	__compound_literal.124
	.long	42
	.zero	4
	.quad	__compound_literal.126
	.long	43
	.zero	4
	.quad	__compound_literal.128
	.long	44
	.zero	4
	.quad	__compound_literal.130
	.long	45
	.zero	4
	.quad	__compound_literal.132
	.long	47
	.zero	4
	.quad	__compound_literal.134
	.long	49
	.zero	4
	.quad	__compound_literal.136
	.long	53
	.zero	4
	.quad	__compound_literal.138
	.long	54
	.zero	4
	.quad	__compound_literal.140
	.long	56
	.zero	4
	.quad	__compound_literal.142
	.long	57
	.zero	4
	.quad	__compound_literal.144
	.long	1
	.zero	4
	.quad	__compound_literal.146
	.long	3
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cstart, @object
	.size	cstate_cstart, 16
cstate_cstart:
	.quad	__compound_literal.147
	.long	0
	.long	89
	.align 4
	.type	__compound_literal.148, @object
	.size	__compound_literal.148, 8
__compound_literal.148:
	.long	183
	.long	183
	.align 16
	.type	__compound_literal.149, @object
	.size	__compound_literal.149, 16
__compound_literal.149:
	.long	0
	.zero	4
	.quad	__compound_literal.148
	.align 32
	.type	__compound_literal.150, @object
	.size	__compound_literal.150, 48
__compound_literal.150:
	.quad	__compound_literal.149
	.long	5
	.zero	4
	.quad	ccall
	.long	2
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_ccall1, @object
	.size	cstate_ccall1, 16
cstate_ccall1:
	.quad	__compound_literal.150
	.long	1
	.long	0
	.align 16
	.type	cstate_ctclass, @object
	.size	cstate_ctclass, 16
cstate_ctclass:
	.quad	0
	.long	3
	.long	0
	.align 32
	.type	__compound_literal.152, @object
	.size	__compound_literal.152, 32
__compound_literal.152:
	.quad	did_tail
	.long	2
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_ccall2, @object
	.size	cstate_ccall2, 16
cstate_ccall2:
	.quad	__compound_literal.152
	.long	2
	.long	0
	.align 32
	.type	__compound_literal.153, @object
	.size	__compound_literal.153, 32
__compound_literal.153:
	.quad	ccall
	.long	4
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cstcall1, @object
	.size	cstate_cstcall1, 16
cstate_cstcall1:
	.quad	__compound_literal.153
	.long	51
	.long	0
	.align 32
	.type	__compound_literal.154, @object
	.size	__compound_literal.154, 32
__compound_literal.154:
	.quad	did_tail
	.long	4
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cstcall2, @object
	.size	cstate_cstcall2, 16
cstate_cstcall2:
	.quad	__compound_literal.154
	.long	4
	.long	0
	.align 4
	.type	__compound_literal.155, @object
	.size	__compound_literal.155, 8
__compound_literal.155:
	.long	114
	.long	114
	.align 16
	.type	__compound_literal.156, @object
	.size	__compound_literal.156, 16
__compound_literal.156:
	.long	0
	.zero	4
	.quad	__compound_literal.155
	.align 4
	.type	__compound_literal.157, @object
	.size	__compound_literal.157, 8
__compound_literal.157:
	.long	99
	.long	99
	.align 16
	.type	__compound_literal.158, @object
	.size	__compound_literal.158, 16
__compound_literal.158:
	.long	0
	.zero	4
	.quad	__compound_literal.157
	.align 4
	.type	__compound_literal.159, @object
	.size	__compound_literal.159, 8
__compound_literal.159:
	.long	101
	.long	101
	.align 16
	.type	__compound_literal.160, @object
	.size	__compound_literal.160, 16
__compound_literal.160:
	.long	0
	.zero	4
	.quad	__compound_literal.159
	.align 32
	.type	__compound_literal.161, @object
	.size	__compound_literal.161, 80
__compound_literal.161:
	.quad	__compound_literal.156
	.long	6
	.zero	4
	.quad	__compound_literal.158
	.long	13
	.zero	4
	.quad	__compound_literal.160
	.long	18
	.zero	4
	.quad	cmethod
	.long	22
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cmethod1, @object
	.size	cstate_cmethod1, 16
cstate_cmethod1:
	.quad	__compound_literal.161
	.long	51
	.long	0
	.align 32
	.type	__compound_literal.162, @object
	.size	__compound_literal.162, 32
__compound_literal.162:
	.quad	did_tail
	.long	22
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cmethod2, @object
	.size	cstate_cmethod2, 16
cstate_cmethod2:
	.quad	__compound_literal.162
	.long	8
	.long	0
	.align 4
	.type	__compound_literal.163, @object
	.size	__compound_literal.163, 8
__compound_literal.163:
	.long	101
	.long	101
	.align 16
	.type	__compound_literal.164, @object
	.size	__compound_literal.164, 16
__compound_literal.164:
	.long	0
	.zero	4
	.quad	__compound_literal.163
	.align 32
	.type	__compound_literal.165, @object
	.size	__compound_literal.165, 48
__compound_literal.165:
	.quad	__compound_literal.164
	.long	7
	.zero	4
	.quad	dnot_e
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.167, @object
	.size	__compound_literal.167, 8
__compound_literal.167:
	.long	113
	.long	113
	.align 16
	.type	__compound_literal.168, @object
	.size	__compound_literal.168, 16
__compound_literal.168:
	.long	0
	.zero	4
	.quad	__compound_literal.167
	.align 32
	.type	__compound_literal.169, @object
	.size	__compound_literal.169, 48
__compound_literal.169:
	.quad	__compound_literal.168
	.long	8
	.zero	4
	.quad	dnot_q
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.171, @object
	.size	__compound_literal.171, 8
__compound_literal.171:
	.long	117
	.long	117
	.align 16
	.type	__compound_literal.172, @object
	.size	__compound_literal.172, 16
__compound_literal.172:
	.long	0
	.zero	4
	.quad	__compound_literal.171
	.align 32
	.type	__compound_literal.173, @object
	.size	__compound_literal.173, 48
__compound_literal.173:
	.quad	__compound_literal.172
	.long	9
	.zero	4
	.quad	dnot_u
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.175, @object
	.size	__compound_literal.175, 8
__compound_literal.175:
	.long	105
	.long	105
	.align 16
	.type	__compound_literal.176, @object
	.size	__compound_literal.176, 16
__compound_literal.176:
	.long	0
	.zero	4
	.quad	__compound_literal.175
	.align 32
	.type	__compound_literal.177, @object
	.size	__compound_literal.177, 48
__compound_literal.177:
	.quad	__compound_literal.176
	.long	10
	.zero	4
	.quad	dnot_i
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.179, @object
	.size	__compound_literal.179, 8
__compound_literal.179:
	.long	114
	.long	114
	.align 16
	.type	__compound_literal.180, @object
	.size	__compound_literal.180, 16
__compound_literal.180:
	.long	0
	.zero	4
	.quad	__compound_literal.179
	.align 32
	.type	__compound_literal.181, @object
	.size	__compound_literal.181, 48
__compound_literal.181:
	.quad	__compound_literal.180
	.long	11
	.zero	4
	.quad	dnot_r
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.183, @object
	.size	__compound_literal.183, 8
__compound_literal.183:
	.long	101
	.long	101
	.align 16
	.type	__compound_literal.184, @object
	.size	__compound_literal.184, 16
__compound_literal.184:
	.long	0
	.zero	4
	.quad	__compound_literal.183
	.align 32
	.type	__compound_literal.185, @object
	.size	__compound_literal.185, 48
__compound_literal.185:
	.quad	__compound_literal.184
	.long	12
	.zero	4
	.quad	dnot_e
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.187, @object
	.size	__compound_literal.187, 32
__compound_literal.187:
	.quad	did_tail
	.long	22
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	cstate_crequire, @object
	.size	cstate_crequire, 112
cstate_crequire:
	.quad	__compound_literal.165
	.long	51
	.long	0
	.quad	__compound_literal.169
	.long	51
	.long	0
	.quad	__compound_literal.173
	.long	51
	.long	0
	.quad	__compound_literal.177
	.long	51
	.long	0
	.quad	__compound_literal.181
	.long	51
	.long	0
	.quad	__compound_literal.185
	.long	51
	.long	0
	.quad	__compound_literal.187
	.long	5
	.long	0
	.align 4
	.type	__compound_literal.189, @object
	.size	__compound_literal.189, 8
__compound_literal.189:
	.long	108
	.long	108
	.align 16
	.type	__compound_literal.190, @object
	.size	__compound_literal.190, 16
__compound_literal.190:
	.long	0
	.zero	4
	.quad	__compound_literal.189
	.align 32
	.type	__compound_literal.191, @object
	.size	__compound_literal.191, 48
__compound_literal.191:
	.quad	__compound_literal.190
	.long	14
	.zero	4
	.quad	dnot_l
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.193, @object
	.size	__compound_literal.193, 8
__compound_literal.193:
	.long	97
	.long	97
	.align 16
	.type	__compound_literal.194, @object
	.size	__compound_literal.194, 16
__compound_literal.194:
	.long	0
	.zero	4
	.quad	__compound_literal.193
	.align 32
	.type	__compound_literal.195, @object
	.size	__compound_literal.195, 48
__compound_literal.195:
	.quad	__compound_literal.194
	.long	15
	.zero	4
	.quad	dnot_a
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.197, @object
	.size	__compound_literal.197, 8
__compound_literal.197:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.198, @object
	.size	__compound_literal.198, 16
__compound_literal.198:
	.long	0
	.zero	4
	.quad	__compound_literal.197
	.align 32
	.type	__compound_literal.199, @object
	.size	__compound_literal.199, 48
__compound_literal.199:
	.quad	__compound_literal.198
	.long	16
	.zero	4
	.quad	dnot_s
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.201, @object
	.size	__compound_literal.201, 8
__compound_literal.201:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.202, @object
	.size	__compound_literal.202, 16
__compound_literal.202:
	.long	0
	.zero	4
	.quad	__compound_literal.201
	.align 32
	.type	__compound_literal.203, @object
	.size	__compound_literal.203, 48
__compound_literal.203:
	.quad	__compound_literal.202
	.long	17
	.zero	4
	.quad	dnot_s
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.205, @object
	.size	__compound_literal.205, 32
__compound_literal.205:
	.quad	did_tail
	.long	22
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	cstate_cclass, @object
	.size	cstate_cclass, 80
cstate_cclass:
	.quad	__compound_literal.191
	.long	51
	.long	0
	.quad	__compound_literal.195
	.long	51
	.long	0
	.quad	__compound_literal.199
	.long	51
	.long	0
	.quad	__compound_literal.203
	.long	51
	.long	0
	.quad	__compound_literal.205
	.long	6
	.long	0
	.align 4
	.type	__compound_literal.207, @object
	.size	__compound_literal.207, 8
__compound_literal.207:
	.long	110
	.long	110
	.align 16
	.type	__compound_literal.208, @object
	.size	__compound_literal.208, 16
__compound_literal.208:
	.long	0
	.zero	4
	.quad	__compound_literal.207
	.align 32
	.type	__compound_literal.209, @object
	.size	__compound_literal.209, 48
__compound_literal.209:
	.quad	__compound_literal.208
	.long	19
	.zero	4
	.quad	dnot_n
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.211, @object
	.size	__compound_literal.211, 8
__compound_literal.211:
	.long	100
	.long	100
	.align 16
	.type	__compound_literal.212, @object
	.size	__compound_literal.212, 16
__compound_literal.212:
	.long	0
	.zero	4
	.quad	__compound_literal.211
	.align 32
	.type	__compound_literal.213, @object
	.size	__compound_literal.213, 48
__compound_literal.213:
	.quad	__compound_literal.212
	.long	20
	.zero	4
	.quad	dnot_d
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.215, @object
	.size	__compound_literal.215, 32
__compound_literal.215:
	.quad	did_tail
	.long	22
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	cstate_cend, @object
	.size	cstate_cend, 48
cstate_cend:
	.quad	__compound_literal.209
	.long	51
	.long	0
	.quad	__compound_literal.213
	.long	51
	.long	0
	.quad	__compound_literal.215
	.long	7
	.long	0
	.align 32
	.type	__compound_literal.217, @object
	.size	__compound_literal.217, 32
__compound_literal.217:
	.quad	ccall
	.long	24
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cinstance1, @object
	.size	cstate_cinstance1, 16
cstate_cinstance1:
	.quad	__compound_literal.217
	.long	51
	.long	0
	.align 32
	.type	__compound_literal.218, @object
	.size	__compound_literal.218, 32
__compound_literal.218:
	.quad	did_tail
	.long	24
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cinstance2, @object
	.size	cstate_cinstance2, 16
cstate_cinstance2:
	.quad	__compound_literal.218
	.long	9
	.long	0
	.align 4
	.type	__compound_literal.219, @object
	.size	__compound_literal.219, 8
__compound_literal.219:
	.long	101
	.long	101
	.align 16
	.type	__compound_literal.220, @object
	.size	__compound_literal.220, 16
__compound_literal.220:
	.long	0
	.zero	4
	.quad	__compound_literal.219
	.align 4
	.type	__compound_literal.221, @object
	.size	__compound_literal.221, 8
__compound_literal.221:
	.long	116
	.long	116
	.align 16
	.type	__compound_literal.222, @object
	.size	__compound_literal.222, 16
__compound_literal.222:
	.long	0
	.zero	4
	.quad	__compound_literal.221
	.align 4
	.type	__compound_literal.223, @object
	.size	__compound_literal.223, 8
__compound_literal.223:
	.long	117
	.long	117
	.align 16
	.type	__compound_literal.224, @object
	.size	__compound_literal.224, 16
__compound_literal.224:
	.long	0
	.zero	4
	.quad	__compound_literal.223
	.align 32
	.type	__compound_literal.225, @object
	.size	__compound_literal.225, 80
__compound_literal.225:
	.quad	dcself1
	.long	39
	.zero	4
	.quad	__compound_literal.220
	.long	26
	.zero	4
	.quad	__compound_literal.222
	.long	34
	.zero	4
	.quad	__compound_literal.224
	.long	30
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cself1, @object
	.size	cstate_cself1, 16
cstate_cself1:
	.quad	__compound_literal.225
	.long	51
	.long	0
	.align 4
	.type	__compound_literal.226, @object
	.size	__compound_literal.226, 8
__compound_literal.226:
	.long	108
	.long	108
	.align 16
	.type	__compound_literal.227, @object
	.size	__compound_literal.227, 16
__compound_literal.227:
	.long	0
	.zero	4
	.quad	__compound_literal.226
	.align 32
	.type	__compound_literal.228, @object
	.size	__compound_literal.228, 48
__compound_literal.228:
	.quad	__compound_literal.227
	.long	27
	.zero	4
	.quad	dnot_l
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.230, @object
	.size	__compound_literal.230, 8
__compound_literal.230:
	.long	102
	.long	102
	.align 16
	.type	__compound_literal.231, @object
	.size	__compound_literal.231, 16
__compound_literal.231:
	.long	0
	.zero	4
	.quad	__compound_literal.230
	.align 32
	.type	__compound_literal.232, @object
	.size	__compound_literal.232, 48
__compound_literal.232:
	.quad	__compound_literal.231
	.long	28
	.zero	4
	.quad	dnot_f
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.234, @object
	.size	__compound_literal.234, 32
__compound_literal.234:
	.quad	did_tail
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	cstate_cself2, @object
	.size	cstate_cself2, 48
cstate_cself2:
	.quad	__compound_literal.228
	.long	51
	.long	0
	.quad	__compound_literal.232
	.long	51
	.long	0
	.quad	__compound_literal.234
	.long	10
	.long	0
	.align 4
	.type	__compound_literal.236, @object
	.size	__compound_literal.236, 8
__compound_literal.236:
	.long	97
	.long	97
	.align 16
	.type	__compound_literal.237, @object
	.size	__compound_literal.237, 16
__compound_literal.237:
	.long	0
	.zero	4
	.quad	__compound_literal.236
	.align 32
	.type	__compound_literal.238, @object
	.size	__compound_literal.238, 48
__compound_literal.238:
	.quad	__compound_literal.237
	.long	35
	.zero	4
	.quad	dnot_a
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.240, @object
	.size	__compound_literal.240, 8
__compound_literal.240:
	.long	116
	.long	116
	.align 16
	.type	__compound_literal.241, @object
	.size	__compound_literal.241, 16
__compound_literal.241:
	.long	0
	.zero	4
	.quad	__compound_literal.240
	.align 32
	.type	__compound_literal.242, @object
	.size	__compound_literal.242, 48
__compound_literal.242:
	.quad	__compound_literal.241
	.long	36
	.zero	4
	.quad	dnot_t
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.244, @object
	.size	__compound_literal.244, 8
__compound_literal.244:
	.long	105
	.long	105
	.align 16
	.type	__compound_literal.245, @object
	.size	__compound_literal.245, 16
__compound_literal.245:
	.long	0
	.zero	4
	.quad	__compound_literal.244
	.align 32
	.type	__compound_literal.246, @object
	.size	__compound_literal.246, 48
__compound_literal.246:
	.quad	__compound_literal.245
	.long	37
	.zero	4
	.quad	dnot_i
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.248, @object
	.size	__compound_literal.248, 8
__compound_literal.248:
	.long	99
	.long	99
	.align 16
	.type	__compound_literal.249, @object
	.size	__compound_literal.249, 16
__compound_literal.249:
	.long	0
	.zero	4
	.quad	__compound_literal.248
	.align 32
	.type	__compound_literal.250, @object
	.size	__compound_literal.250, 48
__compound_literal.250:
	.quad	__compound_literal.249
	.long	38
	.zero	4
	.quad	dnot_c
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.252, @object
	.size	__compound_literal.252, 32
__compound_literal.252:
	.quad	did_tail
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	cstate_cstatic, @object
	.size	cstate_cstatic, 80
cstate_cstatic:
	.quad	__compound_literal.238
	.long	51
	.long	0
	.quad	__compound_literal.242
	.long	51
	.long	0
	.quad	__compound_literal.246
	.long	51
	.long	0
	.quad	__compound_literal.250
	.long	51
	.long	0
	.quad	__compound_literal.252
	.long	12
	.long	0
	.align 4
	.type	__compound_literal.254, @object
	.size	__compound_literal.254, 8
__compound_literal.254:
	.long	112
	.long	112
	.align 16
	.type	__compound_literal.255, @object
	.size	__compound_literal.255, 16
__compound_literal.255:
	.long	0
	.zero	4
	.quad	__compound_literal.254
	.align 32
	.type	__compound_literal.256, @object
	.size	__compound_literal.256, 48
__compound_literal.256:
	.quad	__compound_literal.255
	.long	31
	.zero	4
	.quad	dnot_p
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.258, @object
	.size	__compound_literal.258, 8
__compound_literal.258:
	.long	101
	.long	101
	.align 16
	.type	__compound_literal.259, @object
	.size	__compound_literal.259, 16
__compound_literal.259:
	.long	0
	.zero	4
	.quad	__compound_literal.258
	.align 32
	.type	__compound_literal.260, @object
	.size	__compound_literal.260, 48
__compound_literal.260:
	.quad	__compound_literal.259
	.long	32
	.zero	4
	.quad	dnot_e
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.262, @object
	.size	__compound_literal.262, 8
__compound_literal.262:
	.long	114
	.long	114
	.align 16
	.type	__compound_literal.263, @object
	.size	__compound_literal.263, 16
__compound_literal.263:
	.long	0
	.zero	4
	.quad	__compound_literal.262
	.align 32
	.type	__compound_literal.264, @object
	.size	__compound_literal.264, 48
__compound_literal.264:
	.quad	__compound_literal.263
	.long	33
	.zero	4
	.quad	dnot_r
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.266, @object
	.size	__compound_literal.266, 32
__compound_literal.266:
	.quad	did_tail
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	cstate_csuper, @object
	.size	cstate_csuper, 64
cstate_csuper:
	.quad	__compound_literal.256
	.long	51
	.long	0
	.quad	__compound_literal.260
	.long	51
	.long	0
	.quad	__compound_literal.264
	.long	51
	.long	0
	.quad	__compound_literal.266
	.long	11
	.long	0
	.align 32
	.type	__compound_literal.268, @object
	.size	__compound_literal.268, 32
__compound_literal.268:
	.quad	did_tail
	.long	39
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cid, @object
	.size	cstate_cid, 16
cstate_cid:
	.quad	__compound_literal.268
	.long	13
	.long	0
	.align 16
	.type	cstate_clpare, @object
	.size	cstate_clpare, 16
cstate_clpare:
	.quad	0
	.long	14
	.long	0
	.align 16
	.type	cstate_crpare, @object
	.size	cstate_crpare, 16
cstate_crpare:
	.quad	0
	.long	15
	.long	0
	.align 16
	.type	cstate_clbrace, @object
	.size	cstate_clbrace, 16
cstate_clbrace:
	.quad	0
	.long	16
	.long	0
	.align 16
	.type	cstate_crbrace, @object
	.size	cstate_crbrace, 16
cstate_crbrace:
	.quad	0
	.long	17
	.long	0
	.align 16
	.type	cstate_cquote, @object
	.size	cstate_cquote, 16
cstate_cquote:
	.quad	0
	.long	18
	.long	0
	.align 4
	.type	__compound_literal.274, @object
	.size	__compound_literal.274, 8
__compound_literal.274:
	.long	34
	.long	34
	.align 16
	.type	__compound_literal.275, @object
	.size	__compound_literal.275, 16
__compound_literal.275:
	.long	0
	.zero	4
	.quad	__compound_literal.274
	.align 4
	.type	__compound_literal.276, @object
	.size	__compound_literal.276, 8
__compound_literal.276:
	.long	10
	.long	10
	.align 16
	.type	__compound_literal.277, @object
	.size	__compound_literal.277, 16
__compound_literal.277:
	.long	0
	.zero	4
	.quad	__compound_literal.276
	.align 32
	.type	__compound_literal.278, @object
	.size	__compound_literal.278, 48
__compound_literal.278:
	.quad	__compound_literal.275
	.long	46
	.zero	4
	.quad	__compound_literal.277
	.long	48
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cbslash1, @object
	.size	cstate_cbslash1, 16
cstate_cbslash1:
	.quad	__compound_literal.278
	.long	19
	.long	0
	.align 16
	.type	cstate_cbslash2, @object
	.size	cstate_cbslash2, 16
cstate_cbslash2:
	.quad	0
	.long	20
	.long	0
	.align 16
	.type	cstate_ccatline1, @object
	.size	cstate_ccatline1, 16
cstate_ccatline1:
	.quad	0
	.long	22
	.long	0
	.align 4
	.type	__compound_literal.281, @object
	.size	__compound_literal.281, 8
__compound_literal.281:
	.long	47
	.long	47
	.align 16
	.type	__compound_literal.282, @object
	.size	__compound_literal.282, 16
__compound_literal.282:
	.long	0
	.zero	4
	.quad	__compound_literal.281
	.align 4
	.type	__compound_literal.283, @object
	.size	__compound_literal.283, 8
__compound_literal.283:
	.long	42
	.long	42
	.align 16
	.type	__compound_literal.284, @object
	.size	__compound_literal.284, 16
__compound_literal.284:
	.long	0
	.zero	4
	.quad	__compound_literal.283
	.align 32
	.type	__compound_literal.285, @object
	.size	__compound_literal.285, 48
__compound_literal.285:
	.quad	__compound_literal.282
	.long	50
	.zero	4
	.quad	__compound_literal.284
	.long	51
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cslash1, @object
	.size	cstate_cslash1, 16
cstate_cslash1:
	.quad	__compound_literal.285
	.long	21
	.long	0
	.align 16
	.type	cstate_ccom, @object
	.size	cstate_ccom, 16
cstate_ccom:
	.quad	0
	.long	24
	.long	0
	.align 16
	.type	cstate_ccoms_beg, @object
	.size	cstate_ccoms_beg, 16
cstate_ccoms_beg:
	.quad	0
	.long	25
	.long	0
	.align 4
	.type	__compound_literal.288, @object
	.size	__compound_literal.288, 8
__compound_literal.288:
	.long	47
	.long	47
	.align 16
	.type	__compound_literal.289, @object
	.size	__compound_literal.289, 16
__compound_literal.289:
	.long	0
	.zero	4
	.quad	__compound_literal.288
	.align 32
	.type	__compound_literal.290, @object
	.size	__compound_literal.290, 32
__compound_literal.290:
	.quad	__compound_literal.289
	.long	52
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_cmul, @object
	.size	cstate_cmul, 16
cstate_cmul:
	.quad	__compound_literal.290
	.long	23
	.long	0
	.align 16
	.type	cstate_ccoms_end, @object
	.size	cstate_ccoms_end, 16
cstate_ccoms_end:
	.quad	0
	.long	26
	.long	0
	.align 16
	.type	cstate_cnsign, @object
	.size	cstate_cnsign, 16
cstate_cnsign:
	.quad	0
	.long	27
	.long	0
	.align 16
	.type	cstate_cdeclend, @object
	.size	cstate_cdeclend, 16
cstate_cdeclend:
	.quad	0
	.long	28
	.long	0
	.align 16
	.type	cstate_cspace, @object
	.size	cstate_cspace, 16
cstate_cspace:
	.quad	0
	.long	29
	.long	0
	.align 16
	.type	cstate_cterm, @object
	.size	cstate_cterm, 16
cstate_cterm:
	.quad	0
	.long	30
	.long	0
	.align 16
	.type	cstate_cothers, @object
	.size	cstate_cothers, 16
cstate_cothers:
	.quad	0
	.long	51
	.long	0
	.text
	.globl	cscan_states
	.type	cscan_states, @function
cscan_states:
.LFB31:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	done.3686(%rip), %eax
	testl	%eax, %eax
	je	.L100
	movl	$states.3687, %eax
	jmp	.L101
.L100:
	movq	cstate_cstart(%rip), %rax
	movq	cstate_cstart+8(%rip), %rdx
	movq	%rax, states.3687(%rip)
	movq	%rdx, states.3687+8(%rip)
	movq	cstate_ccall1(%rip), %rax
	movq	cstate_ccall1+8(%rip), %rdx
	movq	%rax, states.3687+16(%rip)
	movq	%rdx, states.3687+24(%rip)
	movq	cstate_ctclass(%rip), %rax
	movq	cstate_ctclass+8(%rip), %rdx
	movq	%rax, states.3687+80(%rip)
	movq	%rdx, states.3687+88(%rip)
	movq	cstate_ccall2(%rip), %rax
	movq	cstate_ccall2+8(%rip), %rdx
	movq	%rax, states.3687+32(%rip)
	movq	%rdx, states.3687+40(%rip)
	movq	cstate_cstcall1(%rip), %rax
	movq	cstate_cstcall1+8(%rip), %rdx
	movq	%rax, states.3687+48(%rip)
	movq	%rdx, states.3687+56(%rip)
	movq	cstate_cstcall2(%rip), %rax
	movq	cstate_cstcall2+8(%rip), %rdx
	movq	%rax, states.3687+64(%rip)
	movq	%rdx, states.3687+72(%rip)
	movq	cstate_cmethod1(%rip), %rax
	movq	cstate_cmethod1+8(%rip), %rdx
	movq	%rax, states.3687+336(%rip)
	movq	%rdx, states.3687+344(%rip)
	movq	cstate_cmethod2(%rip), %rax
	movq	cstate_cmethod2+8(%rip), %rdx
	movq	%rax, states.3687+352(%rip)
	movq	%rdx, states.3687+360(%rip)
	movq	cstate_crequire(%rip), %rax
	movq	cstate_crequire+8(%rip), %rdx
	movq	%rax, states.3687+96(%rip)
	movq	%rdx, states.3687+104(%rip)
	movq	cstate_crequire+16(%rip), %rax
	movq	cstate_crequire+24(%rip), %rdx
	movq	%rax, states.3687+112(%rip)
	movq	%rdx, states.3687+120(%rip)
	movq	cstate_crequire+32(%rip), %rax
	movq	cstate_crequire+40(%rip), %rdx
	movq	%rax, states.3687+128(%rip)
	movq	%rdx, states.3687+136(%rip)
	movq	cstate_crequire+48(%rip), %rax
	movq	cstate_crequire+56(%rip), %rdx
	movq	%rax, states.3687+144(%rip)
	movq	%rdx, states.3687+152(%rip)
	movq	cstate_crequire+64(%rip), %rax
	movq	cstate_crequire+72(%rip), %rdx
	movq	%rax, states.3687+160(%rip)
	movq	%rdx, states.3687+168(%rip)
	movq	cstate_crequire+80(%rip), %rax
	movq	cstate_crequire+88(%rip), %rdx
	movq	%rax, states.3687+176(%rip)
	movq	%rdx, states.3687+184(%rip)
	movq	cstate_crequire+96(%rip), %rax
	movq	cstate_crequire+104(%rip), %rdx
	movq	%rax, states.3687+192(%rip)
	movq	%rdx, states.3687+200(%rip)
	movq	cstate_cclass(%rip), %rax
	movq	cstate_cclass+8(%rip), %rdx
	movq	%rax, states.3687+208(%rip)
	movq	%rdx, states.3687+216(%rip)
	movq	cstate_cclass+16(%rip), %rax
	movq	cstate_cclass+24(%rip), %rdx
	movq	%rax, states.3687+224(%rip)
	movq	%rdx, states.3687+232(%rip)
	movq	cstate_cclass+32(%rip), %rax
	movq	cstate_cclass+40(%rip), %rdx
	movq	%rax, states.3687+240(%rip)
	movq	%rdx, states.3687+248(%rip)
	movq	cstate_cclass+48(%rip), %rax
	movq	cstate_cclass+56(%rip), %rdx
	movq	%rax, states.3687+256(%rip)
	movq	%rdx, states.3687+264(%rip)
	movq	cstate_cclass+64(%rip), %rax
	movq	cstate_cclass+72(%rip), %rdx
	movq	%rax, states.3687+272(%rip)
	movq	%rdx, states.3687+280(%rip)
	movq	cstate_cend(%rip), %rax
	movq	cstate_cend+8(%rip), %rdx
	movq	%rax, states.3687+288(%rip)
	movq	%rdx, states.3687+296(%rip)
	movq	cstate_cend+16(%rip), %rax
	movq	cstate_cend+24(%rip), %rdx
	movq	%rax, states.3687+304(%rip)
	movq	%rdx, states.3687+312(%rip)
	movq	cstate_cend+32(%rip), %rax
	movq	cstate_cend+40(%rip), %rdx
	movq	%rax, states.3687+320(%rip)
	movq	%rdx, states.3687+328(%rip)
	movq	cstate_cinstance1(%rip), %rax
	movq	cstate_cinstance1+8(%rip), %rdx
	movq	%rax, states.3687+368(%rip)
	movq	%rdx, states.3687+376(%rip)
	movq	cstate_cinstance2(%rip), %rax
	movq	cstate_cinstance2+8(%rip), %rdx
	movq	%rax, states.3687+384(%rip)
	movq	%rdx, states.3687+392(%rip)
	movq	cstate_cself1(%rip), %rax
	movq	cstate_cself1+8(%rip), %rdx
	movq	%rax, states.3687+400(%rip)
	movq	%rdx, states.3687+408(%rip)
	movq	cstate_cself2(%rip), %rax
	movq	cstate_cself2+8(%rip), %rdx
	movq	%rax, states.3687+416(%rip)
	movq	%rdx, states.3687+424(%rip)
	movq	cstate_cself2+16(%rip), %rax
	movq	cstate_cself2+24(%rip), %rdx
	movq	%rax, states.3687+432(%rip)
	movq	%rdx, states.3687+440(%rip)
	movq	cstate_cself2+32(%rip), %rax
	movq	cstate_cself2+40(%rip), %rdx
	movq	%rax, states.3687+448(%rip)
	movq	%rdx, states.3687+456(%rip)
	movq	cstate_cstatic(%rip), %rax
	movq	cstate_cstatic+8(%rip), %rdx
	movq	%rax, states.3687+544(%rip)
	movq	%rdx, states.3687+552(%rip)
	movq	cstate_cstatic+16(%rip), %rax
	movq	cstate_cstatic+24(%rip), %rdx
	movq	%rax, states.3687+560(%rip)
	movq	%rdx, states.3687+568(%rip)
	movq	cstate_cstatic+32(%rip), %rax
	movq	cstate_cstatic+40(%rip), %rdx
	movq	%rax, states.3687+576(%rip)
	movq	%rdx, states.3687+584(%rip)
	movq	cstate_cstatic+48(%rip), %rax
	movq	cstate_cstatic+56(%rip), %rdx
	movq	%rax, states.3687+592(%rip)
	movq	%rdx, states.3687+600(%rip)
	movq	cstate_cstatic+64(%rip), %rax
	movq	cstate_cstatic+72(%rip), %rdx
	movq	%rax, states.3687+608(%rip)
	movq	%rdx, states.3687+616(%rip)
	movq	cstate_csuper(%rip), %rax
	movq	cstate_csuper+8(%rip), %rdx
	movq	%rax, states.3687+480(%rip)
	movq	%rdx, states.3687+488(%rip)
	movq	cstate_csuper+16(%rip), %rax
	movq	cstate_csuper+24(%rip), %rdx
	movq	%rax, states.3687+496(%rip)
	movq	%rdx, states.3687+504(%rip)
	movq	cstate_csuper+32(%rip), %rax
	movq	cstate_csuper+40(%rip), %rdx
	movq	%rax, states.3687+512(%rip)
	movq	%rdx, states.3687+520(%rip)
	movq	cstate_csuper+48(%rip), %rax
	movq	cstate_csuper+56(%rip), %rdx
	movq	%rax, states.3687+528(%rip)
	movq	%rdx, states.3687+536(%rip)
	movq	cstate_cid(%rip), %rax
	movq	cstate_cid+8(%rip), %rdx
	movq	%rax, states.3687+624(%rip)
	movq	%rdx, states.3687+632(%rip)
	movq	cstate_clpare(%rip), %rax
	movq	cstate_clpare+8(%rip), %rdx
	movq	%rax, states.3687+640(%rip)
	movq	%rdx, states.3687+648(%rip)
	movq	cstate_crpare(%rip), %rax
	movq	cstate_crpare+8(%rip), %rdx
	movq	%rax, states.3687+656(%rip)
	movq	%rdx, states.3687+664(%rip)
	movq	cstate_clbrace(%rip), %rax
	movq	cstate_clbrace+8(%rip), %rdx
	movq	%rax, states.3687+672(%rip)
	movq	%rdx, states.3687+680(%rip)
	movq	cstate_crbrace(%rip), %rax
	movq	cstate_crbrace+8(%rip), %rdx
	movq	%rax, states.3687+688(%rip)
	movq	%rdx, states.3687+696(%rip)
	movq	cstate_cquote(%rip), %rax
	movq	cstate_cquote+8(%rip), %rdx
	movq	%rax, states.3687+704(%rip)
	movq	%rdx, states.3687+712(%rip)
	movq	cstate_cbslash1(%rip), %rax
	movq	cstate_cbslash1+8(%rip), %rdx
	movq	%rax, states.3687+720(%rip)
	movq	%rdx, states.3687+728(%rip)
	movq	cstate_cbslash2(%rip), %rax
	movq	cstate_cbslash2+8(%rip), %rdx
	movq	%rax, states.3687+736(%rip)
	movq	%rdx, states.3687+744(%rip)
	movq	cstate_ccatline1(%rip), %rax
	movq	cstate_ccatline1+8(%rip), %rdx
	movq	%rax, states.3687+768(%rip)
	movq	%rdx, states.3687+776(%rip)
	movq	cstate_cslash1(%rip), %rax
	movq	cstate_cslash1+8(%rip), %rdx
	movq	%rax, states.3687+752(%rip)
	movq	%rdx, states.3687+760(%rip)
	movq	cstate_ccom(%rip), %rax
	movq	cstate_ccom+8(%rip), %rdx
	movq	%rax, states.3687+800(%rip)
	movq	%rdx, states.3687+808(%rip)
	movq	cstate_ccoms_beg(%rip), %rax
	movq	cstate_ccoms_beg+8(%rip), %rdx
	movq	%rax, states.3687+816(%rip)
	movq	%rdx, states.3687+824(%rip)
	movq	cstate_cmul(%rip), %rax
	movq	cstate_cmul+8(%rip), %rdx
	movq	%rax, states.3687+784(%rip)
	movq	%rdx, states.3687+792(%rip)
	movq	cstate_ccoms_end(%rip), %rax
	movq	cstate_ccoms_end+8(%rip), %rdx
	movq	%rax, states.3687+832(%rip)
	movq	%rdx, states.3687+840(%rip)
	movq	cstate_cnsign(%rip), %rax
	movq	cstate_cnsign+8(%rip), %rdx
	movq	%rax, states.3687+848(%rip)
	movq	%rdx, states.3687+856(%rip)
	movq	cstate_cdeclend(%rip), %rax
	movq	cstate_cdeclend+8(%rip), %rdx
	movq	%rax, states.3687+864(%rip)
	movq	%rdx, states.3687+872(%rip)
	movq	cstate_cspace(%rip), %rax
	movq	cstate_cspace+8(%rip), %rdx
	movq	%rax, states.3687+896(%rip)
	movq	%rdx, states.3687+904(%rip)
	movq	cstate_cterm(%rip), %rax
	movq	cstate_cterm+8(%rip), %rdx
	movq	%rax, states.3687+912(%rip)
	movq	%rdx, states.3687+920(%rip)
	movq	cstate_cothers(%rip), %rax
	movq	cstate_cothers+8(%rip), %rdx
	movq	%rax, states.3687+1424(%rip)
	movq	%rdx, states.3687+1432(%rip)
	movl	$1, done.3686(%rip)
	movl	$states.3687, %eax
.L101:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	cscan_states, .-cscan_states
	.globl	scan_debug
	.type	scan_debug, @function
scan_debug:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L104
	call	__stack_chk_fail
.L104:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	scan_debug, .-scan_debug
	.data
	.align 4
	.type	__compound_literal.297, @object
	.size	__compound_literal.297, 8
__compound_literal.297:
	.long	99
	.long	99
	.align 16
	.type	__compound_literal.298, @object
	.size	__compound_literal.298, 16
__compound_literal.298:
	.long	0
	.zero	4
	.quad	__compound_literal.297
	.align 4
	.type	__compound_literal.299, @object
	.size	__compound_literal.299, 8
__compound_literal.299:
	.long	109
	.long	109
	.align 16
	.type	__compound_literal.300, @object
	.size	__compound_literal.300, 16
__compound_literal.300:
	.long	0
	.zero	4
	.quad	__compound_literal.299
	.align 4
	.type	__compound_literal.301, @object
	.size	__compound_literal.301, 8
__compound_literal.301:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.302, @object
	.size	__compound_literal.302, 16
__compound_literal.302:
	.long	0
	.zero	4
	.quad	__compound_literal.301
	.align 4
	.type	__compound_literal.303, @object
	.size	__compound_literal.303, 8
__compound_literal.303:
	.long	60
	.long	60
	.align 16
	.type	__compound_literal.304, @object
	.size	__compound_literal.304, 16
__compound_literal.304:
	.long	0
	.zero	4
	.quad	__compound_literal.303
	.align 4
	.type	__compound_literal.305, @object
	.size	__compound_literal.305, 8
__compound_literal.305:
	.long	123
	.long	123
	.align 16
	.type	__compound_literal.306, @object
	.size	__compound_literal.306, 16
__compound_literal.306:
	.long	0
	.zero	4
	.quad	__compound_literal.305
	.align 4
	.type	__compound_literal.307, @object
	.size	__compound_literal.307, 8
__compound_literal.307:
	.long	125
	.long	125
	.align 16
	.type	__compound_literal.308, @object
	.size	__compound_literal.308, 16
__compound_literal.308:
	.long	0
	.zero	4
	.quad	__compound_literal.307
	.align 32
	.type	__compound_literal.309, @object
	.size	__compound_literal.309, 144
__compound_literal.309:
	.quad	did_head
	.long	79
	.zero	4
	.quad	dterm1
	.long	80
	.zero	4
	.quad	__compound_literal.298
	.long	58
	.zero	4
	.quad	__compound_literal.300
	.long	63
	.zero	4
	.quad	__compound_literal.302
	.long	70
	.zero	4
	.quad	__compound_literal.304
	.long	76
	.zero	4
	.quad	__compound_literal.306
	.long	77
	.zero	4
	.quad	__compound_literal.308
	.long	78
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	state_start, @object
	.size	state_start, 16
state_start:
	.quad	__compound_literal.309
	.long	51
	.long	0
	.align 4
	.type	__compound_literal.310, @object
	.size	__compound_literal.310, 8
__compound_literal.310:
	.long	108
	.long	108
	.align 16
	.type	__compound_literal.311, @object
	.size	__compound_literal.311, 16
__compound_literal.311:
	.long	0
	.zero	4
	.quad	__compound_literal.310
	.align 32
	.type	__compound_literal.312, @object
	.size	__compound_literal.312, 48
__compound_literal.312:
	.quad	__compound_literal.311
	.long	59
	.zero	4
	.quad	dnot_l
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.314, @object
	.size	__compound_literal.314, 8
__compound_literal.314:
	.long	97
	.long	97
	.align 16
	.type	__compound_literal.315, @object
	.size	__compound_literal.315, 16
__compound_literal.315:
	.long	0
	.zero	4
	.quad	__compound_literal.314
	.align 32
	.type	__compound_literal.316, @object
	.size	__compound_literal.316, 48
__compound_literal.316:
	.quad	__compound_literal.315
	.long	60
	.zero	4
	.quad	dnot_a
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.318, @object
	.size	__compound_literal.318, 8
__compound_literal.318:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.319, @object
	.size	__compound_literal.319, 16
__compound_literal.319:
	.long	0
	.zero	4
	.quad	__compound_literal.318
	.align 32
	.type	__compound_literal.320, @object
	.size	__compound_literal.320, 48
__compound_literal.320:
	.quad	__compound_literal.319
	.long	61
	.zero	4
	.quad	dnot_s
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.322, @object
	.size	__compound_literal.322, 8
__compound_literal.322:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.323, @object
	.size	__compound_literal.323, 16
__compound_literal.323:
	.long	0
	.zero	4
	.quad	__compound_literal.322
	.align 32
	.type	__compound_literal.324, @object
	.size	__compound_literal.324, 48
__compound_literal.324:
	.quad	__compound_literal.323
	.long	62
	.zero	4
	.quad	dnot_s
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.326, @object
	.size	__compound_literal.326, 32
__compound_literal.326:
	.quad	did_tail
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	state_class, @object
	.size	state_class, 80
state_class:
	.quad	__compound_literal.312
	.long	51
	.long	0
	.quad	__compound_literal.316
	.long	51
	.long	0
	.quad	__compound_literal.320
	.long	51
	.long	0
	.quad	__compound_literal.324
	.long	51
	.long	0
	.quad	__compound_literal.326
	.long	37
	.long	0
	.align 4
	.type	__compound_literal.328, @object
	.size	__compound_literal.328, 8
__compound_literal.328:
	.long	116
	.long	116
	.align 16
	.type	__compound_literal.329, @object
	.size	__compound_literal.329, 16
__compound_literal.329:
	.long	0
	.zero	4
	.quad	__compound_literal.328
	.align 32
	.type	__compound_literal.330, @object
	.size	__compound_literal.330, 48
__compound_literal.330:
	.quad	__compound_literal.329
	.long	71
	.zero	4
	.quad	dnot_t
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.332, @object
	.size	__compound_literal.332, 8
__compound_literal.332:
	.long	114
	.long	114
	.align 16
	.type	__compound_literal.333, @object
	.size	__compound_literal.333, 16
__compound_literal.333:
	.long	0
	.zero	4
	.quad	__compound_literal.332
	.align 32
	.type	__compound_literal.334, @object
	.size	__compound_literal.334, 48
__compound_literal.334:
	.quad	__compound_literal.333
	.long	72
	.zero	4
	.quad	dnot_r
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.336, @object
	.size	__compound_literal.336, 8
__compound_literal.336:
	.long	117
	.long	117
	.align 16
	.type	__compound_literal.337, @object
	.size	__compound_literal.337, 16
__compound_literal.337:
	.long	0
	.zero	4
	.quad	__compound_literal.336
	.align 32
	.type	__compound_literal.338, @object
	.size	__compound_literal.338, 48
__compound_literal.338:
	.quad	__compound_literal.337
	.long	73
	.zero	4
	.quad	dnot_u
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.340, @object
	.size	__compound_literal.340, 8
__compound_literal.340:
	.long	99
	.long	99
	.align 16
	.type	__compound_literal.341, @object
	.size	__compound_literal.341, 16
__compound_literal.341:
	.long	0
	.zero	4
	.quad	__compound_literal.340
	.align 32
	.type	__compound_literal.342, @object
	.size	__compound_literal.342, 48
__compound_literal.342:
	.quad	__compound_literal.341
	.long	74
	.zero	4
	.quad	dnot_c
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.344, @object
	.size	__compound_literal.344, 8
__compound_literal.344:
	.long	116
	.long	116
	.align 16
	.type	__compound_literal.345, @object
	.size	__compound_literal.345, 16
__compound_literal.345:
	.long	0
	.zero	4
	.quad	__compound_literal.344
	.align 32
	.type	__compound_literal.346, @object
	.size	__compound_literal.346, 48
__compound_literal.346:
	.quad	__compound_literal.345
	.long	75
	.zero	4
	.quad	dnot_t
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.348, @object
	.size	__compound_literal.348, 32
__compound_literal.348:
	.quad	did_tail
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	state_struct, @object
	.size	state_struct, 96
state_struct:
	.quad	__compound_literal.330
	.long	51
	.long	0
	.quad	__compound_literal.334
	.long	51
	.long	0
	.quad	__compound_literal.338
	.long	51
	.long	0
	.quad	__compound_literal.342
	.long	51
	.long	0
	.quad	__compound_literal.346
	.long	51
	.long	0
	.quad	__compound_literal.348
	.long	41
	.long	0
	.align 4
	.type	__compound_literal.350, @object
	.size	__compound_literal.350, 8
__compound_literal.350:
	.long	101
	.long	101
	.align 16
	.type	__compound_literal.351, @object
	.size	__compound_literal.351, 16
__compound_literal.351:
	.long	0
	.zero	4
	.quad	__compound_literal.350
	.align 32
	.type	__compound_literal.352, @object
	.size	__compound_literal.352, 48
__compound_literal.352:
	.quad	__compound_literal.351
	.long	64
	.zero	4
	.quad	dnot_e
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.354, @object
	.size	__compound_literal.354, 8
__compound_literal.354:
	.long	116
	.long	116
	.align 16
	.type	__compound_literal.355, @object
	.size	__compound_literal.355, 16
__compound_literal.355:
	.long	0
	.zero	4
	.quad	__compound_literal.354
	.align 32
	.type	__compound_literal.356, @object
	.size	__compound_literal.356, 48
__compound_literal.356:
	.quad	__compound_literal.355
	.long	65
	.zero	4
	.quad	dnot_t
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.358, @object
	.size	__compound_literal.358, 8
__compound_literal.358:
	.long	104
	.long	104
	.align 16
	.type	__compound_literal.359, @object
	.size	__compound_literal.359, 16
__compound_literal.359:
	.long	0
	.zero	4
	.quad	__compound_literal.358
	.align 32
	.type	__compound_literal.360, @object
	.size	__compound_literal.360, 48
__compound_literal.360:
	.quad	__compound_literal.359
	.long	66
	.zero	4
	.quad	dnot_h
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.362, @object
	.size	__compound_literal.362, 8
__compound_literal.362:
	.long	111
	.long	111
	.align 16
	.type	__compound_literal.363, @object
	.size	__compound_literal.363, 16
__compound_literal.363:
	.long	0
	.zero	4
	.quad	__compound_literal.362
	.align 32
	.type	__compound_literal.364, @object
	.size	__compound_literal.364, 48
__compound_literal.364:
	.quad	__compound_literal.363
	.long	67
	.zero	4
	.quad	dnot_o
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.366, @object
	.size	__compound_literal.366, 8
__compound_literal.366:
	.long	100
	.long	100
	.align 16
	.type	__compound_literal.367, @object
	.size	__compound_literal.367, 16
__compound_literal.367:
	.long	0
	.zero	4
	.quad	__compound_literal.366
	.align 32
	.type	__compound_literal.368, @object
	.size	__compound_literal.368, 48
__compound_literal.368:
	.quad	__compound_literal.367
	.long	68
	.zero	4
	.quad	dnot_d
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.370, @object
	.size	__compound_literal.370, 8
__compound_literal.370:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.371, @object
	.size	__compound_literal.371, 16
__compound_literal.371:
	.long	0
	.zero	4
	.quad	__compound_literal.370
	.align 32
	.type	__compound_literal.372, @object
	.size	__compound_literal.372, 48
__compound_literal.372:
	.quad	__compound_literal.371
	.long	69
	.zero	4
	.quad	dnot_s
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	__compound_literal.374, @object
	.size	__compound_literal.374, 32
__compound_literal.374:
	.quad	did_tail
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	state_methods, @object
	.size	state_methods, 112
state_methods:
	.quad	__compound_literal.352
	.long	51
	.long	0
	.quad	__compound_literal.356
	.long	51
	.long	0
	.quad	__compound_literal.360
	.long	51
	.long	0
	.quad	__compound_literal.364
	.long	51
	.long	0
	.quad	__compound_literal.368
	.long	51
	.long	0
	.quad	__compound_literal.372
	.long	51
	.long	0
	.quad	__compound_literal.374
	.long	42
	.long	0
	.align 16
	.type	state_extends, @object
	.size	state_extends, 16
state_extends:
	.quad	0
	.long	38
	.long	0
	.align 16
	.type	state_lblock, @object
	.size	state_lblock, 16
state_lblock:
	.quad	0
	.long	39
	.long	0
	.align 16
	.type	state_rblock, @object
	.size	state_rblock, 16
state_rblock:
	.quad	0
	.long	40
	.long	0
	.align 32
	.type	__compound_literal.379, @object
	.size	__compound_literal.379, 32
__compound_literal.379:
	.quad	dterm1
	.long	80
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	state_term, @object
	.size	state_term, 16
state_term:
	.quad	__compound_literal.379
	.long	43
	.long	0
	.align 32
	.type	__compound_literal.380, @object
	.size	__compound_literal.380, 32
__compound_literal.380:
	.quad	did_tail
	.long	79
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	state_id, @object
	.size	state_id, 16
state_id:
	.quad	__compound_literal.380
	.long	45
	.long	0
	.align 16
	.type	state_others, @object
	.size	state_others, 16
state_others:
	.quad	0
	.long	51
	.long	0
	.text
	.globl	scan_states
	.type	scan_states, @function
scan_states:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	done.3792(%rip), %eax
	testl	%eax, %eax
	je	.L106
	movl	$states.3793, %eax
	jmp	.L107
.L106:
	movq	state_start(%rip), %rax
	movq	state_start+8(%rip), %rdx
	movq	%rax, states.3793(%rip)
	movq	%rdx, states.3793+8(%rip)
	movq	state_class(%rip), %rax
	movq	state_class+8(%rip), %rdx
	movq	%rax, states.3793+928(%rip)
	movq	%rdx, states.3793+936(%rip)
	movq	state_class+16(%rip), %rax
	movq	state_class+24(%rip), %rdx
	movq	%rax, states.3793+944(%rip)
	movq	%rdx, states.3793+952(%rip)
	movq	state_class+32(%rip), %rax
	movq	state_class+40(%rip), %rdx
	movq	%rax, states.3793+960(%rip)
	movq	%rdx, states.3793+968(%rip)
	movq	state_class+48(%rip), %rax
	movq	state_class+56(%rip), %rdx
	movq	%rax, states.3793+976(%rip)
	movq	%rdx, states.3793+984(%rip)
	movq	state_class+64(%rip), %rax
	movq	state_class+72(%rip), %rdx
	movq	%rax, states.3793+992(%rip)
	movq	%rdx, states.3793+1000(%rip)
	movq	state_struct(%rip), %rax
	movq	state_struct+8(%rip), %rdx
	movq	%rax, states.3793+1120(%rip)
	movq	%rdx, states.3793+1128(%rip)
	movq	state_struct+16(%rip), %rax
	movq	state_struct+24(%rip), %rdx
	movq	%rax, states.3793+1136(%rip)
	movq	%rdx, states.3793+1144(%rip)
	movq	state_struct+32(%rip), %rax
	movq	state_struct+40(%rip), %rdx
	movq	%rax, states.3793+1152(%rip)
	movq	%rdx, states.3793+1160(%rip)
	movq	state_struct+48(%rip), %rax
	movq	state_struct+56(%rip), %rdx
	movq	%rax, states.3793+1168(%rip)
	movq	%rdx, states.3793+1176(%rip)
	movq	state_struct+64(%rip), %rax
	movq	state_struct+72(%rip), %rdx
	movq	%rax, states.3793+1184(%rip)
	movq	%rdx, states.3793+1192(%rip)
	movq	state_struct+80(%rip), %rax
	movq	state_struct+88(%rip), %rdx
	movq	%rax, states.3793+1200(%rip)
	movq	%rdx, states.3793+1208(%rip)
	movq	state_methods(%rip), %rax
	movq	state_methods+8(%rip), %rdx
	movq	%rax, states.3793+1008(%rip)
	movq	%rdx, states.3793+1016(%rip)
	movq	state_methods+16(%rip), %rax
	movq	state_methods+24(%rip), %rdx
	movq	%rax, states.3793+1024(%rip)
	movq	%rdx, states.3793+1032(%rip)
	movq	state_methods+32(%rip), %rax
	movq	state_methods+40(%rip), %rdx
	movq	%rax, states.3793+1040(%rip)
	movq	%rdx, states.3793+1048(%rip)
	movq	state_methods+48(%rip), %rax
	movq	state_methods+56(%rip), %rdx
	movq	%rax, states.3793+1056(%rip)
	movq	%rdx, states.3793+1064(%rip)
	movq	state_methods+64(%rip), %rax
	movq	state_methods+72(%rip), %rdx
	movq	%rax, states.3793+1072(%rip)
	movq	%rdx, states.3793+1080(%rip)
	movq	state_methods+80(%rip), %rax
	movq	state_methods+88(%rip), %rdx
	movq	%rax, states.3793+1088(%rip)
	movq	%rdx, states.3793+1096(%rip)
	movq	state_methods+96(%rip), %rax
	movq	state_methods+104(%rip), %rdx
	movq	%rax, states.3793+1104(%rip)
	movq	%rdx, states.3793+1112(%rip)
	movq	state_extends(%rip), %rax
	movq	state_extends+8(%rip), %rdx
	movq	%rax, states.3793+1216(%rip)
	movq	%rdx, states.3793+1224(%rip)
	movq	state_lblock(%rip), %rax
	movq	state_lblock+8(%rip), %rdx
	movq	%rax, states.3793+1232(%rip)
	movq	%rdx, states.3793+1240(%rip)
	movq	state_rblock(%rip), %rax
	movq	state_rblock+8(%rip), %rdx
	movq	%rax, states.3793+1248(%rip)
	movq	%rdx, states.3793+1256(%rip)
	movq	state_term(%rip), %rax
	movq	state_term+8(%rip), %rdx
	movq	%rax, states.3793+1280(%rip)
	movq	%rdx, states.3793+1288(%rip)
	movq	state_id(%rip), %rax
	movq	state_id+8(%rip), %rdx
	movq	%rax, states.3793+1264(%rip)
	movq	%rdx, states.3793+1272(%rip)
	movq	state_others(%rip), %rax
	movq	state_others+8(%rip), %rdx
	movq	%rax, states.3793+1424(%rip)
	movq	%rdx, states.3793+1432(%rip)
	movl	$1, done.3792(%rip)
	movl	$states.3793, %eax
.L107:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	scan_states, .-scan_states
	.data
	.align 4
	.type	__compound_literal.382, @object
	.size	__compound_literal.382, 8
__compound_literal.382:
	.long	115
	.long	115
	.align 16
	.type	__compound_literal.383, @object
	.size	__compound_literal.383, 16
__compound_literal.383:
	.long	0
	.zero	4
	.quad	__compound_literal.382
	.align 4
	.type	__compound_literal.384, @object
	.size	__compound_literal.384, 8
__compound_literal.384:
	.long	123
	.long	123
	.align 16
	.type	__compound_literal.385, @object
	.size	__compound_literal.385, 16
__compound_literal.385:
	.long	0
	.zero	4
	.quad	__compound_literal.384
	.align 4
	.type	__compound_literal.386, @object
	.size	__compound_literal.386, 8
__compound_literal.386:
	.long	125
	.long	125
	.align 16
	.type	__compound_literal.387, @object
	.size	__compound_literal.387, 16
__compound_literal.387:
	.long	0
	.zero	4
	.quad	__compound_literal.386
	.align 4
	.type	__compound_literal.388, @object
	.size	__compound_literal.388, 8
__compound_literal.388:
	.long	59
	.long	59
	.align 16
	.type	__compound_literal.389, @object
	.size	__compound_literal.389, 16
__compound_literal.389:
	.long	0
	.zero	4
	.quad	__compound_literal.388
	.align 4
	.type	__compound_literal.390, @object
	.size	__compound_literal.390, 8
__compound_literal.390:
	.long	45
	.long	45
	.align 16
	.type	__compound_literal.391, @object
	.size	__compound_literal.391, 16
__compound_literal.391:
	.long	0
	.zero	4
	.quad	__compound_literal.390
	.align 4
	.type	__compound_literal.392, @object
	.size	__compound_literal.392, 8
__compound_literal.392:
	.long	183
	.long	183
	.align 16
	.type	__compound_literal.393, @object
	.size	__compound_literal.393, 16
__compound_literal.393:
	.long	0
	.zero	4
	.quad	__compound_literal.392
	.align 32
	.type	__compound_literal.394, @object
	.size	__compound_literal.394, 128
__compound_literal.394:
	.quad	dterm1
	.long	80
	.zero	4
	.quad	__compound_literal.383
	.long	81
	.zero	4
	.quad	__compound_literal.385
	.long	77
	.zero	4
	.quad	__compound_literal.387
	.long	78
	.zero	4
	.quad	__compound_literal.389
	.long	86
	.zero	4
	.quad	__compound_literal.391
	.long	85
	.zero	4
	.quad	__compound_literal.393
	.long	87
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_start, @object
	.size	cstate_start, 16
cstate_start:
	.quad	__compound_literal.394
	.long	0
	.long	89
	.align 4
	.type	__compound_literal.395, @object
	.size	__compound_literal.395, 8
__compound_literal.395:
	.long	101
	.long	101
	.align 16
	.type	__compound_literal.396, @object
	.size	__compound_literal.396, 16
__compound_literal.396:
	.long	0
	.zero	4
	.quad	__compound_literal.395
	.align 32
	.type	__compound_literal.397, @object
	.size	__compound_literal.397, 32
__compound_literal.397:
	.quad	__compound_literal.396
	.long	82
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.399, @object
	.size	__compound_literal.399, 8
__compound_literal.399:
	.long	108
	.long	108
	.align 16
	.type	__compound_literal.400, @object
	.size	__compound_literal.400, 16
__compound_literal.400:
	.long	0
	.zero	4
	.quad	__compound_literal.399
	.align 32
	.type	__compound_literal.401, @object
	.size	__compound_literal.401, 32
__compound_literal.401:
	.quad	__compound_literal.400
	.long	83
	.zero	4
	.quad	0
	.zero	8
	.align 4
	.type	__compound_literal.403, @object
	.size	__compound_literal.403, 8
__compound_literal.403:
	.long	102
	.long	102
	.align 16
	.type	__compound_literal.404, @object
	.size	__compound_literal.404, 16
__compound_literal.404:
	.long	0
	.zero	4
	.quad	__compound_literal.403
	.align 32
	.type	__compound_literal.405, @object
	.size	__compound_literal.405, 32
__compound_literal.405:
	.quad	__compound_literal.404
	.long	84
	.zero	4
	.quad	0
	.zero	8
	.align 32
	.type	cstate_self, @object
	.size	cstate_self, 64
cstate_self:
	.quad	__compound_literal.397
	.long	51
	.long	0
	.quad	__compound_literal.401
	.long	51
	.long	0
	.quad	__compound_literal.405
	.long	51
	.long	0
	.quad	0
	.long	44
	.long	0
	.align 16
	.type	cstate_lblock, @object
	.size	cstate_lblock, 16
cstate_lblock:
	.quad	0
	.long	39
	.long	0
	.align 16
	.type	cstate_rblock, @object
	.size	cstate_rblock, 16
cstate_rblock:
	.quad	0
	.long	40
	.long	0
	.align 16
	.type	cstate_stat, @object
	.size	cstate_stat, 16
cstate_stat:
	.quad	0
	.long	48
	.long	0
	.align 4
	.type	__compound_literal.411, @object
	.size	__compound_literal.411, 8
__compound_literal.411:
	.long	183
	.long	183
	.align 16
	.type	__compound_literal.412, @object
	.size	__compound_literal.412, 16
__compound_literal.412:
	.long	0
	.zero	4
	.quad	__compound_literal.411
	.align 32
	.type	__compound_literal.413, @object
	.size	__compound_literal.413, 32
__compound_literal.413:
	.quad	__compound_literal.412
	.long	88
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_tself, @object
	.size	cstate_tself, 16
cstate_tself:
	.quad	__compound_literal.413
	.long	49
	.long	0
	.align 32
	.type	__compound_literal.414, @object
	.size	__compound_literal.414, 32
__compound_literal.414:
	.quad	did_tail
	.long	85
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_method, @object
	.size	cstate_method, 16
cstate_method:
	.quad	__compound_literal.414
	.long	46
	.long	0
	.align 16
	.type	cstate_tclass, @object
	.size	cstate_tclass, 16
cstate_tclass:
	.quad	0
	.long	50
	.long	0
	.align 32
	.type	__compound_literal.416, @object
	.size	__compound_literal.416, 32
__compound_literal.416:
	.quad	dterm1
	.long	80
	.zero	4
	.quad	0
	.zero	8
	.align 16
	.type	cstate_term, @object
	.size	cstate_term, 16
cstate_term:
	.quad	__compound_literal.416
	.long	43
	.long	0
	.align 16
	.type	cstate_others, @object
	.size	cstate_others, 16
cstate_others:
	.quad	0
	.long	51
	.long	0
	.text
	.globl	scan_cstates
	.type	scan_cstates, @function
scan_cstates:
.LFB34:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	done.3843(%rip), %eax
	testl	%eax, %eax
	je	.L109
	movl	$states.3844, %eax
	jmp	.L110
.L109:
	movq	cstate_start(%rip), %rax
	movq	cstate_start+8(%rip), %rdx
	movq	%rax, states.3844(%rip)
	movq	%rdx, states.3844+8(%rip)
	movq	cstate_self(%rip), %rax
	movq	cstate_self+8(%rip), %rdx
	movq	%rax, states.3844+1296(%rip)
	movq	%rdx, states.3844+1304(%rip)
	movq	cstate_self+16(%rip), %rax
	movq	cstate_self+24(%rip), %rdx
	movq	%rax, states.3844+1312(%rip)
	movq	%rdx, states.3844+1320(%rip)
	movq	cstate_self+32(%rip), %rax
	movq	cstate_self+40(%rip), %rdx
	movq	%rax, states.3844+1328(%rip)
	movq	%rdx, states.3844+1336(%rip)
	movq	cstate_self+48(%rip), %rax
	movq	cstate_self+56(%rip), %rdx
	movq	%rax, states.3844+1344(%rip)
	movq	%rdx, states.3844+1352(%rip)
	movq	cstate_lblock(%rip), %rax
	movq	cstate_lblock+8(%rip), %rdx
	movq	%rax, states.3844+1232(%rip)
	movq	%rdx, states.3844+1240(%rip)
	movq	cstate_rblock(%rip), %rax
	movq	cstate_rblock+8(%rip), %rdx
	movq	%rax, states.3844+1248(%rip)
	movq	%rdx, states.3844+1256(%rip)
	movq	cstate_stat(%rip), %rax
	movq	cstate_stat+8(%rip), %rdx
	movq	%rax, states.3844+1376(%rip)
	movq	%rdx, states.3844+1384(%rip)
	movq	cstate_tself(%rip), %rax
	movq	cstate_tself+8(%rip), %rdx
	movq	%rax, states.3844+1392(%rip)
	movq	%rdx, states.3844+1400(%rip)
	movq	cstate_method(%rip), %rax
	movq	cstate_method+8(%rip), %rdx
	movq	%rax, states.3844+1360(%rip)
	movq	%rdx, states.3844+1368(%rip)
	movq	cstate_tclass(%rip), %rax
	movq	cstate_tclass+8(%rip), %rdx
	movq	%rax, states.3844+1408(%rip)
	movq	%rdx, states.3844+1416(%rip)
	movq	cstate_term(%rip), %rax
	movq	cstate_term+8(%rip), %rdx
	movq	%rax, states.3844+1280(%rip)
	movq	%rdx, states.3844+1288(%rip)
	movq	cstate_others(%rip), %rax
	movq	cstate_others+8(%rip), %rdx
	movq	%rax, states.3844+1424(%rip)
	movq	%rdx, states.3844+1432(%rip)
	movl	$1, done.3843(%rip)
	movl	$states.3844, %eax
.L110:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	scan_cstates, .-scan_cstates
	.globl	scan_token
	.type	scan_token, @function
scan_token:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movl	$0, -92(%rbp)
	movl	$0, -88(%rbp)
	leaq	-32(%rbp), %rax
	movq	-112(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	scan_char
	movq	-112(%rbp), %rax
	movq	24(%rax), %rax
	call	*%rax
	movq	%rax, -72(%rbp)
	movq	-112(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	jmp	.L112
.L120:
	movl	-24(%rbp), %eax
	movl	%eax, -84(%rbp)
	movb	$0, -93(%rbp)
	movl	-88(%rbp), %eax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	jmp	.L113
.L116:
	movq	-80(%rbp), %rax
	movq	(%rax), %rdx
	movl	-84(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	scan_is
	testl	%eax, %eax
	je	.L114
	movq	-80(%rbp), %rax
	movl	8(%rax), %eax
	movl	%eax, -88(%rbp)
	movb	$1, -93(%rbp)
	jmp	.L115
.L114:
	addq	$16, -80(%rbp)
.L113:
	cmpq	$0, -80(%rbp)
	je	.L115
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L116
.L115:
	cmpb	$0, -93(%rbp)
	jne	.L117
	movq	-56(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jne	.L118
	movq	-56(%rbp), %rax
	movl	12(%rax), %eax
	movl	%eax, -88(%rbp)
	jmp	.L117
.L118:
	movq	-56(%rbp), %rax
	movl	8(%rax), %eax
	movl	%eax, -92(%rbp)
	jmp	.L119
.L117:
	movq	-112(%rbp), %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movq	-112(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-144(%rbp), %rax
	movq	-112(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	scan_char
	movq	-144(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-128(%rbp), %rax
	movq	%rax, -16(%rbp)
.L112:
	movq	-112(%rbp), %rax
	movq	(%rax), %rdx
	movq	-112(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, %rdx
	jb	.L120
.L119:
	movq	-112(%rbp), %rax
	movq	(%rax), %rax
	subq	-64(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-112(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	scan_debug
	movq	-104(%rbp), %rax
	movl	-92(%rbp), %edx
	movl	%edx, (%rax)
	movq	-104(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-104(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-104(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	scan_token, .-scan_token
	.globl	cscan_new
	.type	cscan_new, @function
cscan_new:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
	movq	$0, 24(%rax)
	movq	$0, 32(%rax)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	$cscan_states, 24(%rax)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	cscan_new, .-cscan_new
	.globl	scan_new
	.type	scan_new, @function
scan_new:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
	movq	$0, 24(%rax)
	movq	$0, 32(%rax)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	$scan_states, 24(%rax)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	scan_new, .-scan_new
	.globl	parse_next
	.type	parse_next, @function
parse_next:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	scan_token
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	parse_next, .-parse_next
	.globl	parse_test
	.type	parse_test, @function
parse_test:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	-12(%rbp), %eax
	sete	%al
	movzbl	%al, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	parse_test, .-parse_test
	.section	.rodata
.LC8:
	.string	"expected token %d, given %d\n"
	.text
	.globl	parse_check
	.type	parse_check, @function
parse_check:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	jne	.L130
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC8, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
.L130:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	parse_check, .-parse_check
	.globl	parse_match
	.type	parse_match, @function
parse_match:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	leaq	-32(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movl	-52(%rbp), %edx
	leaq	-32(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	parse_check
	movq	-40(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-40(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	parse_match, .-parse_match
	.globl	parse_matchp
	.type	parse_matchp, @function
parse_matchp:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rbx
	leaq	-80(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-80(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-72(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rbx)
	movq	-40(%rbp), %rax
	movl	$14, %esi
	movq	%rax, %rdi
	call	parse_test
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE42:
	.size	parse_matchp, .-parse_matchp
	.globl	parse_term
	.type	parse_term, @function
parse_term:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	leaq	-32(%rbp), %rax
	movl	-52(%rbp), %edx
	movq	-48(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	leaq	-96(%rbp), %rax
	movq	-48(%rbp), %rcx
	movl	$43, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	movq	-40(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-40(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	parse_term, .-parse_term
	.section	.rodata
.LC9:
	.string	"ary is already newed."
	.text
	.globl	ary_new
	.type	ary_new, @function
ary_new:
.LFB44:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L139
	movl	$.LC9, %edi
	call	puts
	movl	$0, %edi
	call	exit
.L139:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	ary_new, .-ary_new
	.globl	ary_add
	.type	ary_add, @function
ary_add:
.LFB45:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, %rdx
	jb	.L141
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	leaq	(%rax,%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L142
	movq	-8(%rbp), %rax
	movq	$1, 8(%rax)
.L142:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	imulq	-24(%rbp), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc
	movq	-8(%rbp), %rdx
	movq	%rax, 16(%rdx)
.L141:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rcx
	movq	-8(%rbp), %rdx
	movq	%rcx, (%rdx)
	imulq	-24(%rbp), %rax
	leaq	(%rsi,%rax), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	subq	$1, %rax
	imulq	-24(%rbp), %rax
	addq	%rdx, %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE45:
	.size	ary_add, .-ary_add
	.globl	ary_free
	.type	ary_free, @function
ary_free:
.LFB46:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	ckfree
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE46:
	.size	ary_free, .-ary_free
	.globl	tok_new_str
	.type	tok_new_str, @function
tok_new_str:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE47:
	.size	tok_new_str, .-tok_new_str
	.globl	tok_cat_str
	.type	tok_cat_str, @function
tok_cat_str:
.LFB48:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	-32(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	leaq	(%rdx,%rax), %rcx
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE48:
	.size	tok_cat_str, .-tok_cat_str
	.globl	tok_poffset
	.type	tok_poffset, @function
tok_poffset:
.LFB49:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -40(%rbp)
	jmp	.L150
.L153:
	movq	-56(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -24(%rbp)
	cmpq	$0, -72(%rbp)
	je	.L151
	subq	$1, -72(%rbp)
	jmp	.L152
.L151:
	movl	$0, -16(%rbp)
	movb	$0, -12(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rcx
	leaq	-16(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movq	-64(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs
.L152:
	movq	-24(%rbp), %rax
	addq	%rax, -40(%rbp)
.L150:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	-40(%rbp), %rax
	ja	.L153
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L154
	call	__stack_chk_fail
.L154:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE49:
	.size	tok_poffset, .-tok_poffset
	.globl	tok_ptail
	.type	tok_ptail, @function
tok_ptail:
.LFB50:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	tok_poffset
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE50:
	.size	tok_ptail, .-tok_ptail
	.globl	tok_print
	.type	tok_print, @function
tok_print:
.LFB51:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	tok_poffset
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE51:
	.size	tok_print, .-tok_print
	.globl	tok_first_not_term
	.type	tok_first_not_term, @function
tok_first_not_term:
.LFB52:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	$0, -16(%rbp)
	jmp	.L158
.L161:
	movq	-24(%rbp), %rax
	movq	16(%rax), %rcx
	movq	-16(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$43, %eax
	je	.L159
	jmp	.L160
.L159:
	addq	$1, -16(%rbp)
.L158:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-16(%rbp), %rax
	ja	.L161
.L160:
	movq	-16(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE52:
	.size	tok_first_not_term, .-tok_first_not_term
	.section	.rodata
.LC10:
	.string	"%s_t"
.LC11:
	.string	"%s_class_t"
.LC12:
	.string	"%s_t * "
	.text
	.globl	toks_cprint
	.type	toks_cprint, @function
toks_cprint:
.LFB53:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	jmp	.L164
.L172:
	movq	-40(%rbp), %rax
	movq	144(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	16(%rax), %rcx
	movq	-56(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -20(%rbp)
	cmpl	$49, -20(%rbp)
	je	.L165
	cmpl	$1, -20(%rbp)
	jne	.L166
.L165:
	movq	-16(%rbp), %rdx
	movq	-64(%rbp), %rax
	movl	$.LC10, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L167
.L166:
	cmpl	$50, -20(%rbp)
	je	.L168
	cmpl	$3, -20(%rbp)
	jne	.L169
.L168:
	movq	-16(%rbp), %rdx
	movq	-64(%rbp), %rax
	movl	$.LC11, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L167
.L169:
	cmpl	$44, -20(%rbp)
	je	.L170
	cmpl	$10, -20(%rbp)
	jne	.L171
.L170:
	movq	-16(%rbp), %rdx
	movq	-64(%rbp), %rax
	movl	$.LC12, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-64(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	jmp	.L167
.L171:
	movq	-64(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
.L167:
	addq	$1, -56(%rbp)
.L164:
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-56(%rbp), %rax
	ja	.L172
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE53:
	.size	toks_cprint, .-toks_cprint
	.globl	cparse_require
	.type	cparse_require, @function
cparse_require:
.LFB54:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	leaq	-144(%rbp), %rax
	movq	-96(%rbp), %rcx
	movl	$51, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	leaq	-144(%rbp), %rax
	movq	-96(%rbp), %rcx
	movl	$18, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	leaq	-48(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	ary_new
	movq	-104(%rbp), %rbx
	leaq	-144(%rbp), %rax
	movq	-96(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-144(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-136(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-128(%rbp), %rax
	movq	%rax, 16(%rbx)
	jmp	.L174
.L178:
	movq	-104(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	-104(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -72(%rbp)
	movq	-104(%rbp), %rax
	movl	$20, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L175
	addq	$1, -80(%rbp)
	subq	$1, -72(%rbp)
.L175:
	movq	$0, -64(%rbp)
	jmp	.L176
.L177:
	movq	-64(%rbp), %rax
	movq	-80(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rcx
	leaq	-48(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	addq	$1, -64(%rbp)
.L176:
	movq	-64(%rbp), %rax
	cmpq	-72(%rbp), %rax
	jb	.L177
	movq	-104(%rbp), %rbx
	leaq	-144(%rbp), %rax
	movq	-96(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-144(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-136(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-128(%rbp), %rax
	movq	%rax, 16(%rbx)
.L174:
	movq	-104(%rbp), %rax
	movl	$18, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L178
	movq	-104(%rbp), %rbx
	leaq	-144(%rbp), %rax
	movq	-96(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-144(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-136(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-128(%rbp), %rax
	movq	%rax, 16(%rbx)
	movq	-88(%rbp), %rax
	leaq	8(%rax), %rcx
	leaq	-48(%rbp), %rax
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE54:
	.size	cparse_require, .-cparse_require
	.globl	cparse_raw
	.type	cparse_raw, @function
cparse_raw:
.LFB55:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -32(%rbp)
	jmp	.L180
.L186:
	movq	-32(%rbp), %rax
	testq	%rax, %rax
	jne	.L181
	movl	$48, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$24, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	movq	-40(%rbp), %rax
	leaq	32(%rax), %rcx
	leaq	-32(%rbp), %rax
	movl	$8, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
.L181:
	movq	-56(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L182
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_require
	movq	-56(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rax
	movq	-56(%rbp), %rcx
	movl	$24, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	jmp	.L183
.L182:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L184
	movq	-32(%rbp), %rax
	movq	-56(%rbp), %rcx
	movl	$24, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	movq	%rax, -24(%rbp)
	jmp	.L183
.L184:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 8(%rax)
.L183:
	movq	-56(%rbp), %rbx
	leaq	-96(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-96(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-88(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-80(%rbp), %rax
	movq	%rax, 16(%rbx)
.L180:
	movq	-56(%rbp), %rax
	movl	$6, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	jne	.L179
	movq	-48(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L186
.L179:
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE55:
	.size	cparse_raw, .-cparse_raw
	.globl	tok_cpy
	.type	tok_cpy, @function
tok_cpy:
.LFB56:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$24, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	(%rdx), %rcx
	movq	%rcx, (%rax)
	movq	8(%rdx), %rcx
	movq	%rcx, 8(%rax)
	movq	16(%rdx), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE56:
	.size	tok_cpy, .-tok_cpy
	.globl	cal_add_cpy
	.type	cal_add_cpy, @function
cal_add_cpy:
.LFB57:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	tok_cpy
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	leaq	-8(%rbp), %rcx
	movl	$8, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE57:
	.size	cal_add_cpy, .-cal_add_cpy
	.globl	cparse_terms
	.type	cparse_terms, @function
cparse_terms:
.LFB58:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-56(%rbp), %rbx
	leaq	-96(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-96(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-88(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-80(%rbp), %rax
	movq	%rax, 16(%rbx)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	jmp	.L192
.L193:
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-56(%rbp), %rbx
	leaq	-96(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-96(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-88(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-80(%rbp), %rax
	movq	%rax, 16(%rbx)
.L192:
	movq	-56(%rbp), %rax
	movl	$30, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	jne	.L193
	movq	-24(%rbp), %rax
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE58:
	.size	cparse_terms, .-cparse_terms
	.globl	cparse_def
	.type	cparse_def, @function
cparse_def:
.LFB59:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$232, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movq	%rdx, -200(%rbp)
	movq	%rcx, -208(%rbp)
	movq	-200(%rbp), %rax
	movq	$scan_states, 24(%rax)
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$43, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	movq	-192(%rbp), %rbx
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$45, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_term
	movq	-240(%rbp), %rax
	movq	%rax, 24(%rbx)
	movq	-232(%rbp), %rax
	movq	%rax, 32(%rbx)
	movq	-224(%rbp), %rax
	movq	%rax, 40(%rbx)
	leaq	-160(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	leaq	-160(%rbp), %rax
	movl	$38, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L196
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$43, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	movq	-192(%rbp), %rbx
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$45, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_term
	movq	-240(%rbp), %rax
	movq	%rax, 48(%rbx)
	movq	-232(%rbp), %rax
	movq	%rax, 56(%rbx)
	movq	-224(%rbp), %rax
	movq	%rax, 64(%rbx)
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$39, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_term
	jmp	.L197
.L196:
	movq	-192(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	$6, %rax
	jne	.L198
	movq	-168(%rbp), %rax
	movq	16(%rax), %rax
	movl	$6, %edx
	movl	$basename.4055, %esi
	movq	%rax, %rdi
	call	memcmp
	testl	%eax, %eax
	je	.L199
.L198:
	movq	-192(%rbp), %rax
	movq	base.4056(%rip), %rdx
	movq	%rdx, 48(%rax)
	movq	base.4056+8(%rip), %rdx
	movq	%rdx, 56(%rax)
	movq	base.4056+16(%rip), %rdx
	movq	%rdx, 64(%rax)
.L199:
	leaq	-160(%rbp), %rax
	movl	$39, %esi
	movq	%rax, %rdi
	call	parse_check
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$43, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
.L197:
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$41, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_term
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$39, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	movq	$1, -176(%rbp)
	movq	-200(%rbp), %rax
	movq	$scan_cstates, 24(%rax)
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-240(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-192(%rbp), %rax
	addq	$72, %rax
	movl	$24, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	movq	-192(%rbp), %rax
	leaq	72(%rax), %rcx
	leaq	-160(%rbp), %rax
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
.L204:
	leaq	-160(%rbp), %rax
	movl	$39, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L200
	addq	$1, -176(%rbp)
	jmp	.L201
.L200:
	leaq	-160(%rbp), %rax
	movl	$40, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L201
	subq	$1, -176(%rbp)
.L201:
	cmpq	$0, -176(%rbp)
	jne	.L202
	nop
	movq	-200(%rbp), %rax
	movq	$scan_states, 24(%rax)
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$43, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-240(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -144(%rbp)
	leaq	-160(%rbp), %rax
	movl	$37, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L205
	jmp	.L216
.L202:
	movq	-192(%rbp), %rax
	leaq	72(%rax), %rcx
	leaq	-160(%rbp), %rax
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-240(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -144(%rbp)
	jmp	.L204
.L216:
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$43, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$39, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	movq	-200(%rbp), %rax
	movq	$scan_cstates, 24(%rax)
	leaq	-96(%rbp), %rsi
	movl	$0, %eax
	movl	$9, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movq	-192(%rbp), %rax
	addq	$96, %rax
	movl	$72, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	ary_new
.L214:
	leaq	-128(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	leaq	-128(%rbp), %rax
	movl	$40, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L206
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	ary_free
	movq	-200(%rbp), %rax
	movq	$scan_states, 24(%rax)
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$43, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	leaq	-240(%rbp), %rax
	movq	-200(%rbp), %rcx
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_match
	jmp	.L207
.L206:
	leaq	-128(%rbp), %rax
	movl	$46, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L208
	movq	-128(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -56(%rbp)
	jmp	.L209
.L208:
	leaq	-128(%rbp), %rax
	movl	$48, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L210
	movq	-192(%rbp), %rax
	leaq	96(%rax), %rcx
	leaq	-96(%rbp), %rax
	movl	$72, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	leaq	-96(%rbp), %rsi
	movl	$0, %eax
	movl	$9, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	jmp	.L209
.L210:
	movq	-80(%rbp), %rax
	testq	%rax, %rax
	jne	.L211
	leaq	-96(%rbp), %rax
	movl	$24, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	leaq	-128(%rbp), %rcx
	leaq	-96(%rbp), %rax
	movl	$24, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	jmp	.L209
.L211:
	movq	-56(%rbp), %rax
	testq	%rax, %rax
	jne	.L212
	leaq	-128(%rbp), %rcx
	leaq	-96(%rbp), %rax
	movl	$24, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	jmp	.L209
.L212:
	movq	-32(%rbp), %rax
	testq	%rax, %rax
	jne	.L213
	leaq	-96(%rbp), %rax
	addq	$48, %rax
	movl	$24, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	leaq	-128(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	48(%rdx), %rcx
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	jmp	.L209
.L213:
	leaq	-128(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	48(%rdx), %rcx
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	jmp	.L214
.L209:
	jmp	.L214
.L205:
	movq	-192(%rbp), %rax
	addq	$96, %rax
	movl	$72, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	leaq	-160(%rbp), %rax
	movl	$40, %esi
	movq	%rax, %rdi
	call	parse_check
.L207:
	movq	-200(%rbp), %rax
	movq	$cscan_states, 24(%rax)
	movq	-208(%rbp), %rdx
	movq	-200(%rbp), %rcx
	movq	-192(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_terms
	addq	$232, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE59:
	.size	cparse_def, .-cparse_def
	.globl	cal_add_cat
	.type	cal_add_cat, @function
cal_add_cat:
.LFB60:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	tok_cpy
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	8(%rdx), %rcx
	movq	-40(%rbp), %rdx
	movq	8(%rdx), %rdx
	addq	%rcx, %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	leaq	-8(%rbp), %rcx
	movl	$8, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE60:
	.size	cal_add_cat, .-cal_add_cat
	.globl	cal_add_two
	.type	cal_add_two, @function
cal_add_two:
.LFB61:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$48, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	(%rdx), %rcx
	movq	%rcx, (%rax)
	movq	8(%rdx), %rcx
	movq	%rcx, 8(%rax)
	movq	16(%rdx), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	(%rdx), %rcx
	movq	%rcx, 24(%rax)
	movq	8(%rdx), %rcx
	movq	%rcx, 32(%rax)
	movq	16(%rdx), %rdx
	movq	%rdx, 40(%rax)
	movq	-24(%rbp), %rax
	leaq	-8(%rbp), %rcx
	movl	$8, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE61:
	.size	cal_add_two, .-cal_add_two
	.globl	cparse_call
	.type	cparse_call, @function
cparse_call:
.LFB62:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	leaq	-32(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	leaq	-32(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L220
	movq	-56(%rbp), %rax
	movl	$34, (%rax)
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cal_add_two
	jmp	.L219
.L220:
	leaq	-32(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L222
	movq	-56(%rbp), %rax
	movl	$35, (%rax)
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cal_add_two
	jmp	.L219
.L222:
	leaq	-32(%rbp), %rax
	movl	$29, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L223
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	leaq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L219
.L223:
	leaq	-32(%rbp), %rax
	movl	$30, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L224
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	leaq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L219
.L224:
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cal_add_cat
.L219:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE62:
	.size	cparse_call, .-cparse_call
	.globl	cparse_scall
	.type	cparse_scall, @function
cparse_scall:
.LFB63:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	leaq	-32(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	leaq	-32(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L226
	movq	-56(%rbp), %rax
	movl	$32, (%rax)
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cal_add_two
	jmp	.L225
.L226:
	leaq	-32(%rbp), %rax
	movl	$14, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L228
	movq	-56(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	(%rdx), %rcx
	movq	%rcx, (%rax)
	movq	8(%rdx), %rcx
	movq	%rcx, 8(%rax)
	movq	16(%rdx), %rdx
	movq	%rdx, 16(%rax)
	movq	-56(%rbp), %rax
	movl	$31, (%rax)
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	leaq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L225
.L228:
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cal_add_cat
.L225:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE63:
	.size	cparse_scall, .-cparse_scall
	.globl	cparse_cmeth
	.type	cparse_cmeth, @function
cparse_cmeth:
.LFB64:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$200, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	%rdx, -168(%rbp)
	movq	%rcx, -176(%rbp)
	movq	-168(%rbp), %rdx
	movq	-152(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	%rax, -144(%rbp)
	movq	-152(%rbp), %rax
	leaq	120(%rax), %rcx
	leaq	-144(%rbp), %rax
	movl	$8, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	movq	$0, -136(%rbp)
	movq	-168(%rbp), %rbx
	leaq	-208(%rbp), %rax
	movq	-160(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-208(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-200(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-192(%rbp), %rax
	movq	%rax, 16(%rbx)
	movq	-168(%rbp), %rax
	movl	$14, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L230
	leaq	-96(%rbp), %rsi
	movl	$0, %eax
	movl	$9, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	leaq	-96(%rbp), %rax
	movl	$24, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-152(%rbp), %rax
	movq	16(%rax), %rax
	movq	-128(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movl	$12, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L231
	addq	$1, -128(%rbp)
	movq	-152(%rbp), %rax
	movq	16(%rax), %rax
	movq	-128(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -120(%rbp)
	jmp	.L232
.L233:
	addq	$1, -128(%rbp)
	movq	-152(%rbp), %rax
	movq	16(%rax), %rax
	movq	-128(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -120(%rbp)
.L232:
	movq	-120(%rbp), %rax
	movl	$29, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	jne	.L233
.L231:
	jmp	.L234
.L236:
	movq	-152(%rbp), %rax
	movq	16(%rax), %rax
	movq	-128(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movl	$30, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	jne	.L235
	movq	-104(%rbp), %rcx
	leaq	-96(%rbp), %rax
	movl	$24, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ary_add
.L235:
	addq	$1, -128(%rbp)
.L234:
	movq	-112(%rbp), %rax
	subq	$1, %rax
	cmpq	-128(%rbp), %rax
	ja	.L236
	movq	-168(%rbp), %rdx
	movq	-152(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	leaq	-96(%rbp), %rax
	addq	$48, %rax
	movl	$24, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	movq	-168(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	48(%rdx), %rcx
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	addq	$1, -136(%rbp)
	movq	-144(%rbp), %rax
	movq	(%rax), %rdx
	movq	%rdx, -72(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -64(%rbp)
	movq	16(%rax), %rax
	movq	%rax, -56(%rbp)
	movl	$47, -72(%rbp)
.L241:
	movq	-168(%rbp), %rbx
	leaq	-208(%rbp), %rax
	movq	-160(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-208(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-200(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-192(%rbp), %rax
	movq	%rax, 16(%rbx)
	movq	-168(%rbp), %rdx
	movq	-152(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-168(%rbp), %rax
	movl	$15, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L237
	subq	$1, -136(%rbp)
	cmpq	$0, -136(%rbp)
	jne	.L238
	movq	-168(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	48(%rdx), %rcx
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	movq	-152(%rbp), %rax
	leaq	96(%rax), %rcx
	leaq	-96(%rbp), %rax
	movl	$72, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	nop
	jmp	.L229
.L237:
	movq	-168(%rbp), %rax
	movl	$14, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L238
	addq	$1, -136(%rbp)
.L238:
	movq	-168(%rbp), %rax
	movl	$30, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	jne	.L240
	movq	-168(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	48(%rdx), %rcx
	movl	$24, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	jmp	.L241
.L240:
	jmp	.L241
.L230:
	movq	-168(%rbp), %rdx
	movq	-152(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
.L229:
	addq	$200, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE64:
	.size	cparse_cmeth, .-cparse_cmeth
	.globl	cparse_com
	.type	cparse_com, @function
cparse_com:
.LFB65:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-40(%rbp), %rbx
	leaq	-80(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-80(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-72(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rbx)
	jmp	.L244
.L245:
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-40(%rbp), %rbx
	leaq	-80(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-80(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-72(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rbx)
.L244:
	movq	-40(%rbp), %rax
	movl	$30, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L245
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_terms
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE65:
	.size	cparse_com, .-cparse_com
	.globl	cparse_coms
	.type	cparse_coms, @function
cparse_coms:
.LFB66:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-40(%rbp), %rbx
	leaq	-80(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-80(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-72(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rbx)
	jmp	.L248
.L249:
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-40(%rbp), %rbx
	leaq	-80(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-80(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-72(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rbx)
.L248:
	movq	-40(%rbp), %rax
	movl	$26, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L249
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_terms
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE66:
	.size	cparse_coms, .-cparse_coms
	.globl	cparse_src
	.type	cparse_src, @function
cparse_src:
.LFB67:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	movq	-88(%rbp), %rax
	movl	$6, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L251
	movl	$160, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -64(%rbp)
	movq	-72(%rbp), %rax
	leaq	32(%rax), %rcx
	leaq	-64(%rbp), %rax
	movl	$8, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_add
	movq	-64(%rbp), %rax
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	ary_new
	movq	-64(%rbp), %rsi
	movq	-88(%rbp), %rcx
	movq	-80(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	cparse_def
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rax
	movq	96(%rax), %rax
	movq	-64(%rbp), %rdx
	leaq	120(%rdx), %rcx
	movl	$8, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	ary_new
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	jmp	.L254
.L272:
	movq	-88(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L255
	movq	-88(%rbp), %rbx
	leaq	-128(%rbp), %rax
	movq	-80(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-128(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-120(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-112(%rbp), %rax
	movq	%rax, 16(%rbx)
	nop
	jmp	.L251
.L255:
	movq	-88(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L257
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L258
.L257:
	movq	-88(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L259
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L258
.L259:
	movq	-88(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L260
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movq	%rdx, -48(%rbp)
	movq	8(%rax), %rdx
	movq	%rdx, -40(%rbp)
	movq	16(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rcx
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rsi
	movq	%rax, %rdi
	call	cparse_cmeth
	jmp	.L258
.L260:
	movq	-88(%rbp), %rax
	movl	$10, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L261
	movq	-88(%rbp), %rax
	movl	$13, (%rax)
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L258
.L261:
	movq	-88(%rbp), %rax
	movl	$11, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L262
	movq	-64(%rbp), %rax
	leaq	-48(%rbp), %rcx
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rsi
	movq	%rax, %rdi
	call	cparse_scall
	jmp	.L258
.L262:
	movq	-88(%rbp), %rax
	movl	$13, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L263
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_call
	jmp	.L258
.L263:
	movq	-88(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L264
	movq	-88(%rbp), %rax
	movl	$33, (%rax)
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L258
.L264:
	movq	-88(%rbp), %rax
	movl	$9, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L265
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L258
.L265:
	movq	-88(%rbp), %rax
	movl	$14, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L266
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	jmp	.L258
.L266:
	movq	-88(%rbp), %rax
	movl	$27, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L267
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_com
	movq	%rax, -56(%rbp)
	jmp	.L254
.L267:
	movq	-88(%rbp), %rax
	movl	$24, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L268
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_com
	movq	%rax, -56(%rbp)
	jmp	.L254
.L268:
	movq	-88(%rbp), %rax
	movl	$25, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L269
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_coms
	movq	%rax, -56(%rbp)
	jmp	.L254
.L269:
	movq	-88(%rbp), %rax
	movl	$28, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L270
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_terms
	movq	%rax, -56(%rbp)
	jmp	.L254
.L270:
	movq	-88(%rbp), %rax
	movl	$17, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	je	.L271
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_terms
	movq	%rax, -56(%rbp)
	jmp	.L254
.L271:
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cal_add_cpy
.L258:
	movq	-88(%rbp), %rbx
	leaq	-128(%rbp), %rax
	movq	-80(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	movq	-128(%rbp), %rax
	movq	%rax, (%rbx)
	movq	-120(%rbp), %rax
	movq	%rax, 8(%rbx)
	movq	-112(%rbp), %rax
	movq	%rax, 16(%rbx)
.L254:
	movq	-88(%rbp), %rax
	movl	$6, %esi
	movq	%rax, %rdi
	call	parse_test
	testl	%eax, %eax
	jne	.L251
	movq	-80(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L272
.L251:
	addq	$120, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE67:
	.size	cparse_src, .-cparse_src
	.globl	cparse_header
	.type	cparse_header, @function
cparse_header:
.LFB68:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movl	$64, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	addq	$8, %rax
	movl	$24, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	ary_new
	movq	-88(%rbp), %rax
	addq	$32, %rax
	movl	$8, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	ary_new
	leaq	-48(%rbp), %rax
	movq	-112(%rbp), %rdx
	movq	-104(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cscan_new
	leaq	-80(%rbp), %rax
	leaq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_next
	jmp	.L274
.L275:
	leaq	-80(%rbp), %rdx
	leaq	-48(%rbp), %rcx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_raw
	leaq	-80(%rbp), %rdx
	leaq	-48(%rbp), %rcx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cparse_src
.L274:
	movq	-16(%rbp), %rax
	testq	%rax, %rax
	je	.L275
	movq	-88(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE68:
	.size	cparse_header, .-cparse_header
	.globl	str_is_upcase
	.type	str_is_upcase, @function
str_is_upcase:
.LFB69:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$64, -4(%rbp)
	jbe	.L278
	cmpb	$90, -4(%rbp)
	ja	.L278
	movl	$1, %eax
	jmp	.L279
.L278:
	movl	$0, %eax
.L279:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE69:
	.size	str_is_upcase, .-str_is_upcase
	.globl	str_is_dwcase
	.type	str_is_dwcase, @function
str_is_dwcase:
.LFB70:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$96, -4(%rbp)
	jbe	.L282
	cmpb	$122, -4(%rbp)
	ja	.L282
	movl	$1, %eax
	jmp	.L283
.L282:
	movl	$0, %eax
.L283:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE70:
	.size	str_is_dwcase, .-str_is_dwcase
	.globl	tok_word
	.type	tok_word, @function
tok_word:
.LFB71:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	jmp	.L286
.L288:
	movq	-48(%rbp), %rax
	movq	-72(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -24(%rbp)
	cmpq	$1, -24(%rbp)
	jne	.L287
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	str_is_upcase
	testl	%eax, %eax
	je	.L287
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-24(%rbp), %rax
	addq	%rax, -48(%rbp)
	addq	$1, -56(%rbp)
.L286:
	movq	-48(%rbp), %rax
	cmpq	-80(%rbp), %rax
	jb	.L288
.L287:
	cmpq	$1, -56(%rbp)
	ja	.L289
	jmp	.L290
.L293:
	movq	-48(%rbp), %rax
	movq	-72(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -8(%rbp)
	cmpq	$1, -8(%rbp)
	jne	.L291
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	str_is_upcase
	testl	%eax, %eax
	je	.L291
	nop
	jmp	.L294
.L291:
	movq	-8(%rbp), %rax
	addq	%rax, -48(%rbp)
.L290:
	movq	-48(%rbp), %rax
	cmpq	-80(%rbp), %rax
	jb	.L293
	jmp	.L294
.L289:
	movq	-40(%rbp), %rax
	movq	%rax, -48(%rbp)
.L294:
	movq	-48(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE71:
	.size	tok_word, .-tok_word
	.globl	tok_words
	.type	tok_words, @function
tok_words:
.LFB72:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$56, %rsp
	movq	%rdi, -56(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	jmp	.L297
.L299:
	movq	-56(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	subq	-32(%rbp), %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_word
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L298
	addq	$1, -40(%rbp)
	movq	-8(%rbp), %rax
	addq	%rax, -32(%rbp)
	jmp	.L297
.L298:
	movq	-16(%rbp), %rax
	addq	%rax, -32(%rbp)
.L297:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	-32(%rbp), %rax
	ja	.L299
	cmpq	$0, -40(%rbp)
	jne	.L300
	movq	$1, -40(%rbp)
.L300:
	movq	-40(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE72:
	.size	tok_words, .-tok_words
	.globl	str_upcase
	.type	str_upcase, @function
str_upcase:
.LFB73:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	subl	$32, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE73:
	.size	str_upcase, .-str_upcase
	.globl	str_dwcase
	.type	str_dwcase, @function
str_dwcase:
.LFB74:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	addl	$32, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE74:
	.size	str_dwcase, .-str_dwcase
	.globl	tok_case
	.type	tok_case, @function
tok_case:
.LFB75:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%rcx, -80(%rbp)
	movq	%r8, -88(%rbp)
	movq	$0, -40(%rbp)
	jmp	.L307
.L309:
	movq	-40(%rbp), %rax
	movq	-64(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rax
	movq	-56(%rbp), %rdx
	leaq	(%rdx,%rax), %rcx
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
	cmpq	$1, -24(%rbp)
	jne	.L308
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %edi
	call	*%rax
	testl	%eax, %eax
	je	.L308
	movq	-40(%rbp), %rax
	movq	-56(%rbp), %rdx
	leaq	(%rdx,%rax), %rbx
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %edx
	movq	-88(%rbp), %rax
	movl	%edx, %edi
	call	*%rax
	movb	%al, (%rbx)
.L308:
	movq	-24(%rbp), %rax
	addq	%rax, -40(%rbp)
.L307:
	movq	-40(%rbp), %rax
	cmpq	-72(%rbp), %rax
	jb	.L309
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE75:
	.size	tok_case, .-tok_case
	.globl	tok_upcase
	.type	tok_upcase, @function
tok_upcase:
.LFB76:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movl	$str_upcase, %r8d
	movl	$str_is_dwcase, %ecx
	movq	%rax, %rdi
	call	tok_case
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE76:
	.size	tok_upcase, .-tok_upcase
	.globl	tok_dwcase
	.type	tok_dwcase, @function
tok_dwcase:
.LFB77:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movl	$str_dwcase, %r8d
	movl	$str_is_upcase, %ecx
	movq	%rax, %rdi
	call	tok_case
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE77:
	.size	tok_dwcase, .-tok_dwcase
	.globl	tok_inflect
	.type	tok_inflect, @function
tok_inflect:
.LFB78:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	$0, -32(%rbp)
	jmp	.L313
.L316:
	movq	-48(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	utf8_len
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	subq	-32(%rbp), %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_word
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L314
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rsi
	movq	-40(%rbp), %rcx
	movq	-56(%rbp), %rax
	movq	%rcx, %rdi
	call	*%rax
	movq	-8(%rbp), %rax
	addq	%rax, -32(%rbp)
	movq	-8(%rbp), %rax
	addq	%rax, -40(%rbp)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	-32(%rbp), %rax
	jbe	.L313
	movq	-40(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -40(%rbp)
	movb	$95, (%rax)
	jmp	.L313
.L314:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movq	-16(%rbp), %rax
	addq	%rax, -32(%rbp)
	movq	-16(%rbp), %rax
	addq	%rax, -40(%rbp)
.L313:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	-32(%rbp), %rax
	ja	.L316
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE78:
	.size	tok_inflect, .-tok_inflect
	.globl	tok_constantize
	.type	tok_constantize, @function
tok_constantize:
.LFB79:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$tok_upcase, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	tok_inflect
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE79:
	.size	tok_constantize, .-tok_constantize
	.globl	tok_underscore
	.type	tok_underscore, @function
tok_underscore:
.LFB80:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$tok_dwcase, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	tok_inflect
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE80:
	.size	tok_underscore, .-tok_underscore
	.globl	class_inflect
	.type	class_inflect, @function
class_inflect:
.LFB81:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rbx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	tok_words
	addq	%rbx, %rax
	leaq	-1(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_new_str
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	movq	-24(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE81:
	.size	class_inflect, .-class_inflect
	.globl	class_classes
	.type	class_classes, @function
class_classes:
.LFB82:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -32(%rbp)
	call	h_init
	movq	%rax, -24(%rbp)
	movq	$0, -40(%rbp)
	jmp	.L322
.L324:
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	movq	-40(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L323
	movq	-16(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	h_insert
.L323:
	addq	$1, -40(%rbp)
.L322:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-40(%rbp), %rax
	ja	.L324
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE82:
	.size	class_classes, .-class_classes
	.globl	class_source
	.type	class_source, @function
class_source:
.LFB83:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	-72(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cparse_header
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	class_classes
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -48(%rbp)
	jmp	.L327
.L328:
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	addq	$48, %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movl	$tok_underscore, %esi
	movq	%rax, %rdi
	call	class_inflect
	movq	-24(%rbp), %rdx
	movq	%rax, 144(%rdx)
	movq	-8(%rbp), %rax
	movl	$tok_underscore, %esi
	movq	%rax, %rdi
	call	class_inflect
	movq	-24(%rbp), %rdx
	movq	%rax, 152(%rdx)
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	movq	%rax, -48(%rbp)
.L327:
	cmpq	$0, -48(%rbp)
	jne	.L328
	movq	-40(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 56(%rax)
	movq	-40(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE83:
	.size	class_source, .-class_source
	.section	.rodata
.LC13:
	.string	"Please require "
.LC14:
	.string	"."
	.text
	.globl	class_crmeths
	.type	class_crmeths, @function
class_crmeths:
.LFB84:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L330
	movq	-96(%rbp), %rax
	addq	$48, %rax
	movq	%rax, -48(%rbp)
	movq	$0, -64(%rbp)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-88(%rbp), %rax
	movq	56(%rax), %rax
	leaq	-64(%rbp), %rcx
	movq	%rax, %rdi
	call	h_get
	movl	%eax, -68(%rbp)
	cmpl	$0, -68(%rbp)
	jne	.L333
	movq	-48(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L333
	movl	$.LC13, %edi
	movl	$0, %eax
	call	printf
	movq	stdout(%rip), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movl	$.LC14, %edi
	call	puts
	movl	$0, %edi
	call	exit
.L333:
	movq	-64(%rbp), %rcx
	movq	-104(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	class_crmeths
	movq	-96(%rbp), %rax
	movq	96(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	$0, -56(%rbp)
	jmp	.L334
.L335:
	movq	-96(%rbp), %rax
	movq	112(%rax), %rcx
	movq	-56(%rbp), %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	subq	$1, %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	h_insert
	addq	$1, -56(%rbp)
.L334:
	movq	-56(%rbp), %rax
	cmpq	-40(%rbp), %rax
	jb	.L335
.L330:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE84:
	.size	class_crmeths, .-class_crmeths
	.globl	class_cmeths
	.type	class_cmeths, @function
class_cmeths:
.LFB85:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	call	h_init
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	class_crmeths
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE85:
	.size	class_cmeths, .-class_cmeths
	.section	.rodata
.LC15:
	.string	"%s_class_t "
.LC16:
	.string	";\n\n"
	.text
	.globl	class_pclass
	.type	class_pclass, @function
class_pclass:
.LFB86:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	144(%rax), %rdx
	movq	-16(%rbp), %rax
	movl	$.LC15, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-8(%rbp), %rax
	leaq	24(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	tok_print
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC16, %edi
	call	fwrite
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE86:
	.size	class_pclass, .-class_pclass
	.globl	class_praw
	.type	class_praw, @function
class_praw:
.LFB87:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	$0, -24(%rbp)
	jmp	.L340
.L341:
	movq	-16(%rbp), %rax
	movq	16(%rax), %rcx
	movq	-24(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	movq	-48(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	addq	$1, -24(%rbp)
.L340:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-24(%rbp), %rax
	ja	.L341
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE87:
	.size	class_praw, .-class_praw
	.section	.rodata
.LC17:
	.string	", "
	.text
	.globl	class_parg
	.type	class_parg, @function
class_parg:
.LFB88:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$14, %eax
	jne	.L343
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$15, %eax
	je	.L342
	movq	-32(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC17, %edi
	call	fwrite
	jmp	.L342
.L343:
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$41, %edi
	call	fputc
.L342:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE88:
	.size	class_parg, .-class_parg
	.section	.rodata
.LC18:
	.string	"%s_method_"
.LC19:
	.string	"self->"
.LC20:
	.string	"self->_.super->"
.LC21:
	.string	"(self"
.LC22:
	.string	"self->_->"
.LC23:
	.string	"->_->"
.LC24:
	.string	"._->"
	.text
	.globl	class_psrc
	.type	class_psrc, @function
class_psrc:
.LFB89:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	$0, -64(%rbp)
	jmp	.L347
.L350:
	movq	-56(%rbp), %rax
	movq	16(%rax), %rax
	movq	-64(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -72(%rbp)
	cmpl	$30, -72(%rbp)
	je	.L348
	jmp	.L349
.L348:
	movq	-64(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -64(%rbp)
.L347:
	movq	-56(%rbp), %rax
	movq	(%rax), %rdx
	movq	-64(%rbp), %rax
	cmpq	%rax, %rdx
	ja	.L350
.L349:
	movq	-88(%rbp), %rax
	movq	144(%rax), %rax
	movq	%rax, -40(%rbp)
	jmp	.L351
.L363:
	movq	-56(%rbp), %rax
	movq	16(%rax), %rax
	movq	-64(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-56(%rbp), %rax
	movq	16(%rax), %rax
	movq	-64(%rbp), %rdx
	addq	$1, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-56(%rbp), %rax
	movq	16(%rax), %rax
	movq	-64(%rbp), %rdx
	addq	$2, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -68(%rbp)
	cmpl	$1, -68(%rbp)
	jne	.L352
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC10, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L353
.L352:
	cmpl	$3, -68(%rbp)
	jne	.L354
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC11, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L353
.L354:
	cmpl	$8, -68(%rbp)
	jne	.L355
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC18, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	jmp	.L353
.L355:
	cmpl	$10, -68(%rbp)
	jne	.L356
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC12, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	jmp	.L353
.L356:
	cmpl	$9, -68(%rbp)
	jne	.L357
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$6, %edx
	movl	$1, %esi
	movl	$.LC19, %edi
	call	fwrite
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	jmp	.L353
.L357:
	cmpl	$31, -68(%rbp)
	jne	.L358
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$15, %edx
	movl	$1, %esi
	movl	$.LC20, %edi
	call	fwrite
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movl	$.LC21, %edi
	call	fwrite
	movq	-96(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_parg
	jmp	.L353
.L358:
	cmpl	$32, -68(%rbp)
	jne	.L359
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$15, %edx
	movl	$1, %esi
	movl	$.LC20, %edi
	call	fwrite
	movq	-96(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movl	$.LC21, %edi
	call	fwrite
	movq	-96(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_parg
	jmp	.L353
.L359:
	cmpl	$33, -68(%rbp)
	jne	.L360
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$9, %edx
	movl	$1, %esi
	movl	$.LC22, %edi
	call	fwrite
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movl	$.LC21, %edi
	call	fwrite
	movq	-96(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_parg
	jmp	.L353
.L360:
	cmpl	$34, -68(%rbp)
	jne	.L361
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movl	$.LC23, %edi
	call	fwrite
	movq	-96(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$40, %edi
	call	fputc
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-96(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_parg
	jmp	.L353
.L361:
	cmpl	$35, -68(%rbp)
	jne	.L362
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movl	$.LC24, %edi
	call	fwrite
	movq	-96(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$40, %edi
	call	fputc
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-96(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_parg
	jmp	.L353
.L362:
	movq	-96(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
.L353:
	movq	-64(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -64(%rbp)
.L351:
	movq	-56(%rbp), %rax
	movq	(%rax), %rdx
	movq	-64(%rbp), %rax
	cmpq	%rax, %rdx
	ja	.L363
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE89:
	.size	class_psrc, .-class_psrc
	.section	.rodata
.LC25:
	.string	"\n\n"
.LC26:
	.string	"void\n"
.LC27:
	.string	"%s_class_init(void) {\n"
.LC28:
	.string	"  class_init(&"
.LC29:
	.string	", 0"
.LC30:
	.string	"  %s_class_init();\n"
.LC31:
	.string	"  o_init_class((Object *) &"
.LC32:
	.string	", (Object *) &"
.LC33:
	.string	", \""
.LC34:
	.string	"\",\n"
	.align 8
.LC35:
	.string	"    sizeof(%s_class_t), sizeof(%s_t));\n"
.LC36:
	.string	"  "
.LC37:
	.string	" = %s_method_"
.LC38:
	.string	";\n"
.LC39:
	.string	"}\n\n"
	.text
	.globl	class_pmeth
	.type	class_pmeth, @function
class_pmeth:
.LFB90:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -88(%rbp)
	cmpq	$1, -88(%rbp)
	jbe	.L365
	movq	$2, -88(%rbp)
.L365:
	movq	$0, -80(%rbp)
	jmp	.L366
.L368:
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	subq	-80(%rbp), %rax
	subq	$1, %rax
	movq	%rax, -64(%rbp)
	movq	-72(%rbp), %rax
	movq	16(%rax), %rax
	movq	-64(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -92(%rbp)
	cmpl	$30, -92(%rbp)
	je	.L367
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC25, %edi
	call	fwrite
.L367:
	addq	$1, -80(%rbp)
.L366:
	movq	-80(%rbp), %rax
	cmpq	-88(%rbp), %rax
	jb	.L368
	movq	-104(%rbp), %rax
	movq	144(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-104(%rbp), %rax
	movq	152(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-104(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -32(%rbp)
	movq	-104(%rbp), %rax
	addq	$48, %rax
	movq	%rax, -24(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movl	$.LC26, %edi
	call	fwrite
	movq	-48(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	$.LC27, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-104(%rbp), %rax
	movq	64(%rax), %rax
	testq	%rax, %rax
	jne	.L369
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$14, %edx
	movl	$1, %esi
	movl	$.LC28, %edi
	call	fwrite
	movq	-112(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC29, %edi
	call	fwrite
	jmp	.L370
.L369:
	movq	-40(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	$.LC30, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$27, %edx
	movl	$1, %esi
	movl	$.LC31, %edi
	call	fwrite
	movq	-112(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$14, %edx
	movl	$1, %esi
	movl	$.LC32, %edi
	call	fwrite
	movq	-112(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
.L370:
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC33, %edi
	call	fwrite
	movq	-112(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC34, %edi
	call	fwrite
	movq	-48(%rbp), %rcx
	movq	-48(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	$.LC35, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-104(%rbp), %rax
	addq	$120, %rax
	movq	%rax, -16(%rbp)
	movq	$0, -80(%rbp)
	jmp	.L371
.L372:
	movq	-16(%rbp), %rax
	movq	16(%rax), %rax
	movq	-80(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC36, %edi
	call	fwrite
	movq	-112(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_print
	movq	-112(%rbp), %rax
	movq	%rax, %rsi
	movl	$46, %edi
	call	fputc
	movq	-112(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-48(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	$.LC37, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-112(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC38, %edi
	call	fwrite
	addq	$1, -80(%rbp)
.L371:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-80(%rbp), %rax
	ja	.L372
	movq	-112(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC39, %edi
	call	fwrite
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE90:
	.size	class_pmeth, .-class_pmeth
	.globl	class_pstruct
	.type	class_pstruct, @function
class_pstruct:
.LFB91:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-32(%rbp), %rax
	addq	$48, %rax
	movq	%rax, -8(%rbp)
	movq	$0, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rsi
	leaq	-16(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	h_get
	movq	-32(%rbp), %rax
	movq	64(%rax), %rax
	testq	%rax, %rax
	je	.L374
	movq	-16(%rbp), %rsi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_pstruct
.L374:
	movq	-32(%rbp), %rax
	leaq	72(%rax), %rsi
	movq	-48(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movq	%rax, %rdi
	call	toks_cprint
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE91:
	.size	class_pstruct, .-class_pstruct
	.section	.rodata
	.align 8
.LC40:
	.string	"typedef struct %s_class %s_class_t;\n"
.LC41:
	.string	"typedef struct %s %s_t;\n\n"
.LC42:
	.string	"extern %s_class_t "
.LC43:
	.string	"struct %s_class {\n"
.LC44:
	.string	" (* "
.LC45:
	.string	"};\n\n"
.LC46:
	.string	"  struct %s {"
.LC47:
	.string	"void %s_class_init(void);\n\n"
	.text
	.globl	class_pstructs
	.type	class_pstructs, @function
class_pstructs:
.LFB92:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-88(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -72(%rbp)
	jmp	.L376
.L382:
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	144(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC40, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-40(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC41, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC42, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-48(%rbp), %rax
	leaq	24(%rax), %rdx
	movq	-96(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	tok_print
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC16, %edi
	call	fwrite
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC43, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-48(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	class_cmeths
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -64(%rbp)
	jmp	.L377
.L381:
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L378
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC36, %edi
	call	fwrite
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	tok_first_not_term
	cltq
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rsi
	movq	-96(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	toks_cprint
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$47, %eax
	jne	.L379
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movl	$.LC44, %edi
	call	fwrite
	movq	-96(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
	movq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$41, %edi
	call	fputc
	jmp	.L380
.L379:
	movq	-96(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_ptail
.L380:
	movq	-24(%rbp), %rax
	leaq	48(%rax), %rsi
	movq	-96(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rcx
	movl	$0, %edx
	movq	%rax, %rdi
	call	toks_cprint
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC38, %edi
	call	fwrite
.L378:
	movq	-64(%rbp), %rax
	movq	48(%rax), %rax
	movq	%rax, -64(%rbp)
.L377:
	cmpq	$0, -64(%rbp)
	jne	.L381
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	h_free
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movl	$.LC45, %edi
	call	fwrite
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC46, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-96(%rbp), %rcx
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	class_pstruct
	movq	-96(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movl	$.LC45, %edi
	call	fwrite
	movq	-40(%rbp), %rdx
	movq	-96(%rbp), %rax
	movl	$.LC47, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-72(%rbp), %rax
	movq	48(%rax), %rax
	movq	%rax, -72(%rbp)
.L376:
	cmpq	$0, -72(%rbp)
	jne	.L382
	movq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$10, %edi
	call	fputc
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE92:
	.size	class_pstructs, .-class_pstructs
	.globl	class_freqs
	.type	class_freqs, @function
class_freqs:
.LFB93:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -16(%rbp)
	movq	$0, -24(%rbp)
	jmp	.L384
.L385:
	movq	-16(%rbp), %rax
	movq	16(%rax), %rcx
	movq	-24(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ary_free
	addq	$1, -24(%rbp)
.L384:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-24(%rbp), %rax
	ja	.L385
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	ary_free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE93:
	.size	class_freqs, .-class_freqs
	.globl	class_ftoks
	.type	class_ftoks, @function
class_ftoks:
.LFB94:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L387
	movq	$0, -24(%rbp)
	jmp	.L388
.L389:
	movq	-16(%rbp), %rax
	movq	16(%rax), %rax
	movq	-24(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
	addq	$1, -24(%rbp)
.L388:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-24(%rbp), %rax
	ja	.L389
.L387:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	ary_free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE94:
	.size	class_ftoks, .-class_ftoks
	.globl	class_fstruct
	.type	class_fstruct, @function
class_fstruct:
.LFB95:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$72, %rax
	movq	%rax, %rdi
	call	ary_free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE95:
	.size	class_fstruct, .-class_fstruct
	.globl	class_fmeths
	.type	class_fmeths, @function
class_fmeths:
.LFB96:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	96(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	$0, -24(%rbp)
	jmp	.L392
.L395:
	movq	-40(%rbp), %rax
	movq	112(%rax), %rcx
	movq	-24(%rbp), %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	jne	.L393
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ary_free
	jmp	.L394
.L393:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ary_free
	movq	-8(%rbp), %rax
	addq	$48, %rax
	movq	%rax, %rdi
	call	ary_free
.L394:
	addq	$1, -24(%rbp)
.L392:
	movq	-24(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jb	.L395
	movq	-40(%rbp), %rax
	addq	$96, %rax
	movq	%rax, %rdi
	call	ary_free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE96:
	.size	class_fmeths, .-class_fmeths
	.globl	class_fimps
	.type	class_fimps, @function
class_fimps:
.LFB97:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$120, %rax
	movq	%rax, %rdi
	call	ary_free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE97:
	.size	class_fimps, .-class_fimps
	.globl	class_fsrc
	.type	class_fsrc, @function
class_fsrc:
.LFB98:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L398
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	class_fimps
	movq	-8(%rbp), %rax
	movq	152(%rax), %rax
	movq	%rax, %rdi
	call	ckfree
	jmp	.L397
.L398:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
.L397:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE98:
	.size	class_fsrc, .-class_fsrc
	.globl	class_fsrcs
	.type	class_fsrcs, @function
class_fsrcs:
.LFB99:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -16(%rbp)
	movq	$0, -24(%rbp)
	jmp	.L401
.L402:
	movq	-16(%rbp), %rax
	movq	16(%rax), %rax
	movq	-24(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	class_ftoks
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	class_fsrc
	addq	$1, -24(%rbp)
.L401:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-24(%rbp), %rax
	ja	.L402
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	ary_free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE99:
	.size	class_fsrcs, .-class_fsrcs
	.globl	class_free
	.type	class_free, @function
class_free:
.LFB100:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	class_freqs
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	class_fsrcs
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE100:
	.size	class_free, .-class_free
	.globl	class_fclasses
	.type	class_fclasses, @function
class_fclasses:
.LFB101:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	-56(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -40(%rbp)
	jmp	.L405
.L406:
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_fstruct
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	class_fmeths
	movq	-24(%rbp), %rax
	movq	144(%rax), %rax
	movq	%rax, %rdi
	call	ckfree
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
	movq	-40(%rbp), %rax
	movq	48(%rax), %rax
	movq	%rax, -40(%rbp)
.L405:
	cmpq	$0, -40(%rbp)
	jne	.L406
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	h_free
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -40(%rbp)
	jmp	.L407
.L409:
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	cmpq	-72(%rbp), %rax
	je	.L408
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
.L408:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	ckfree
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
	movq	-40(%rbp), %rax
	movq	48(%rax), %rax
	movq	%rax, -40(%rbp)
.L407:
	cmpq	$0, -40(%rbp)
	jne	.L409
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	h_free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE101:
	.size	class_fclasses, .-class_fclasses
	.globl	class_require
	.type	class_require, @function
class_require:
.LFB102:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	movq	-88(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-88(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -48(%rbp)
	movq	$0, -64(%rbp)
	jmp	.L411
.L413:
	movq	-48(%rbp), %rax
	movq	16(%rax), %rcx
	movq	-64(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tok_new_str
	movq	%rax, -16(%rbp)
	leaq	-88(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	h_get
	movl	%eax, -68(%rbp)
	cmpl	$0, -68(%rbp)
	jne	.L412
	movq	-104(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rcx
	movl	$build_source, %edx
	movq	%rax, %rsi
	movl	$1, %edi
	call	file_read
	movq	%rax, -88(%rbp)
.L412:
	movq	-88(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	h_merge
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	h_free
	addq	$1, -64(%rbp)
.L411:
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-64(%rbp), %rax
	ja	.L413
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE102:
	.size	class_require, .-class_require
	.section	.rodata
.LC48:
	.string	"Generating %s ... "
.LC49:
	.string	"w"
.LC50:
	.string	"OK"
	.text
	.globl	build_source
	.type	build_source, @function
build_source:
.LFB103:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	movq	%rcx, -112(%rbp)
	movq	-104(%rbp), %rdx
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	class_source
	movq	%rax, -64(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rdx
	movq	-64(%rbp), %rcx
	movq	-88(%rbp), %rsi
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	h_insert
	movq	-112(%rbp), %rdx
	movq	-88(%rbp), %rcx
	movq	-64(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	class_require
	movw	$25390, -80(%rbp)
	movb	$0, -78(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rbx
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rsi
	leaq	-80(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rbx, %rcx
	movq	%rax, %rdi
	call	tok_cat_str
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC48, %edi
	movl	$0, %eax
	call	printf
	movq	-56(%rbp), %rax
	movl	$.LC49, %esi
	movq	%rax, %rdi
	call	fopen
	movq	%rax, -48(%rbp)
	movq	-64(%rbp), %rax
	addq	$32, %rax
	movq	%rax, -40(%rbp)
	movq	$0, -72(%rbp)
	jmp	.L415
.L418:
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	-72(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L416
	jmp	.L417
.L416:
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	class_praw
	addq	$1, -72(%rbp)
.L415:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-72(%rbp), %rax
	ja	.L418
.L417:
	movq	-48(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	class_pstructs
	jmp	.L419
.L422:
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	-72(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	jne	.L420
	movq	-48(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	class_praw
	jmp	.L421
.L420:
	movq	-48(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	class_pclass
	movq	-48(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	class_psrc
	movq	-48(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	class_pmeth
.L421:
	addq	$1, -72(%rbp)
.L419:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-72(%rbp), %rax
	ja	.L422
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	movl	$.LC50, %edi
	call	puts
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	ckfree
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	class_free
	movq	-64(%rbp), %rax
	addq	$104, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE103:
	.size	build_source, .-build_source
	.globl	build_source_start
	.type	build_source_start, @function
build_source_start:
.LFB104:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	call	h_init
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	build_source
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	class_fclasses
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE104:
	.size	build_source_start, .-build_source_start
	.section	.rodata
.LC51:
	.string	"no input file"
.LC52:
	.string	"-h"
	.text
	.globl	scan_args
	.type	scan_args, @function
scan_args:
.LFB105:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L426
	movl	$.LC51, %edi
	call	puts
	movl	$0, %edi
	call	exit
.L426:
	cmpl	$2, -4(%rbp)
	jne	.L427
	movl	$0, %eax
	jmp	.L428
.L427:
	cmpl	$3, -4(%rbp)
	jne	.L429
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$.LC52, %esi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	jne	.L429
	movl	$1, %eax
	jmp	.L428
.L429:
	movl	$2, %eax
.L428:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE105:
	.size	scan_args, .-scan_args
	.globl	main
	.type	main, @function
main:
.LFB106:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rdx
	movl	-20(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	scan_args
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L433
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	-20(%rbp), %edx
	leal	-1(%rdx), %edi
	movl	$0, %ecx
	movl	$build_source_start, %edx
	movq	%rax, %rsi
	call	file_read
.L433:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE106:
	.size	main, .-main
	.local	len.2907
	.comm	len.2907,8,8
	.local	done.3686
	.comm	done.3686,4,4
	.local	states.3687
	.comm	states.3687,1440,32
	.local	done.3792
	.comm	done.3792,4,4
	.local	states.3793
	.comm	states.3793,1440,32
	.local	done.3843
	.comm	done.3843,4,4
	.local	states.3844
	.comm	states.3844,1440,32
	.data
	.type	basename.4055, @object
	.size	basename.4055, 7
basename.4055:
	.string	"Object"
	.align 16
	.type	base.4056, @object
	.size	base.4056, 24
base.4056:
	.long	45
	.zero	4
	.quad	6
	.quad	basename.4055
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
