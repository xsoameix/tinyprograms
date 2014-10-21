	.file	"ary_pointer.c"
	.text
.Ltext0:
	.section	.rodata
.LC0:
	.string	"%hd "
.LC1:
	.string	""
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.file 1 "ary_pointer.c"
	.loc 1 5 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	.loc 1 6 0
	movw	$0, -48(%rbp)
	movw	$1, -46(%rbp)
	movw	$2, -44(%rbp)
	movw	$3, -42(%rbp)
	movw	$4, -40(%rbp)
	movw	$5, -38(%rbp)
	movw	$6, -36(%rbp)
	movw	$7, -34(%rbp)
	movw	$8, -32(%rbp)
	movw	$9, -30(%rbp)
	movw	$10, -28(%rbp)
	movw	$11, -26(%rbp)
	movw	$12, -24(%rbp)
	movw	$13, -22(%rbp)
	movw	$14, -20(%rbp)
	movw	$15, -18(%rbp)
	movw	$16, -16(%rbp)
	movw	$17, -14(%rbp)
	movw	$18, -12(%rbp)
	movw	$19, -10(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, -56(%rbp)
	.loc 1 8 0
	movw	$0, -62(%rbp)
	.loc 1 9 0
	movl	$4, -60(%rbp)
	.loc 1 10 0
	jmp	.L2
.L3:
	.loc 1 12 0 discriminator 2
	movswq	-62(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	cwtl
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	.loc 1 10 0 discriminator 2
	movzwl	-62(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -62(%rbp)
.L2:
	.loc 1 10 0 is_stmt 0 discriminator 1
	movswl	-62(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L3
	.loc 1 14 0 is_stmt 1
	movl	$.LC1, %edi
	call	puts
	.loc 1 15 0
	movw	$0, -62(%rbp)
	.loc 1 16 0
	jmp	.L4
.L5:
	.loc 1 18 0 discriminator 2
	movswq	-62(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	.loc 1 16 0 discriminator 2
	movzwl	-62(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -62(%rbp)
.L4:
	.loc 1 16 0 is_stmt 0 discriminator 1
	movswl	-62(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L5
	.loc 1 20 0 is_stmt 1
	movl	$.LC1, %edi
	call	puts
	.loc 1 21 0
	movw	$0, -62(%rbp)
	.loc 1 22 0
	jmp	.L6
.L7:
	.loc 1 24 0 discriminator 2
	movswq	-62(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	cwtl
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	.loc 1 22 0 discriminator 2
	movzwl	-62(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -62(%rbp)
.L6:
	.loc 1 22 0 is_stmt 0 discriminator 1
	movswl	-62(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L7
	.loc 1 26 0 is_stmt 1
	movl	$.LC1, %edi
	call	puts
	.loc 1 27 0
	movw	$0, -62(%rbp)
	.loc 1 28 0
	jmp	.L8
.L9:
	.loc 1 30 0 discriminator 2
	movswq	-62(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	.loc 1 28 0 discriminator 2
	movzwl	-62(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -62(%rbp)
.L8:
	.loc 1 28 0 is_stmt 0 discriminator 1
	movswl	-62(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L9
	.loc 1 32 0 is_stmt 1
	movl	$.LC1, %edi
	call	puts
	.loc 1 33 0
	movl	$0, %eax
	.loc 1 34 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xc3
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF9
	.byte	0x1
	.long	.LASF10
	.long	.LASF11
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF8
	.uleb128 0x4
	.long	.LASF12
	.byte	0x1
	.byte	0x5
	.long	0x57
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0xc0
	.uleb128 0x5
	.string	"i"
	.byte	0x1
	.byte	0x6
	.long	0xc0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x5
	.string	"ary"
	.byte	0x1
	.byte	0x8
	.long	0x50
	.uleb128 0x3
	.byte	0x91
	.sleb128 -78
	.uleb128 0x5
	.string	"len"
	.byte	0x1
	.byte	0x9
	.long	0x57
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x50
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF9:
	.string	"GNU C 4.8.2 -mtune=generic -march=x86-64 -g -fstack-protector"
.LASF3:
	.string	"unsigned int"
.LASF10:
	.string	"ary_pointer.c"
.LASF0:
	.string	"long unsigned int"
.LASF8:
	.string	"char"
.LASF1:
	.string	"unsigned char"
.LASF12:
	.string	"main"
.LASF6:
	.string	"long int"
.LASF11:
	.string	"/home/lien/tinyprogram"
.LASF2:
	.string	"short unsigned int"
.LASF7:
	.string	"sizetype"
.LASF5:
	.string	"short int"
.LASF4:
	.string	"signed char"
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
