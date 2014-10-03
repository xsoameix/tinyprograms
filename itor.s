	.file	"itor.c"
	.intel_syntax noprefix
	.text
	.globl	_itor
	.def	_itor;	.scl	2;	.type	32;	.endef
_itor:
	push	ebp
	mov	ebp, esp
	sub	esp, 24
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_isDone
	leave
	ret
	.globl	_some
	.def	_some;	.scl	2;	.type	32;	.endef
_some:
	push	ebp
	mov	ebp, esp
	sub	esp, 40
	mov	DWORD PTR [ebp-12], 1
	mov	eax, DWORD PTR _a
	mov	DWORD PTR [esp+4], OFFSET FLAT:_itor
	mov	DWORD PTR [esp], eax
	call	_all
	leave
	ret
	.ident	"GCC: (GNU) 4.8.2"
	.def	_isDone;	.scl	2;	.type	32;	.endef
	.def	_all;	.scl	2;	.type	32;	.endef
