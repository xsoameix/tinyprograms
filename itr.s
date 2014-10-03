	.file	"itr.c"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 192
	mov	DWORD PTR [ebp-172], 0
	mov	DWORD PTR [ebp-168], 0
	mov	DWORD PTR [ebp-164], 0
	mov	DWORD PTR [ebp-172], 33
	mov	DWORD PTR [ebp-160], 0
	mov	DWORD PTR [ebp-156], 0
	mov	DWORD PTR [ebp-152], 0
	mov	DWORD PTR [ebp-160], 44
	mov	eax, DWORD PTR [ebp-172]
	mov	DWORD PTR [ebp-148], eax
	mov	eax, DWORD PTR [ebp-168]
	mov	DWORD PTR [ebp-144], eax
	mov	eax, DWORD PTR [ebp-164]
	mov	DWORD PTR [ebp-140], eax
	mov	eax, DWORD PTR [ebp-160]
	mov	DWORD PTR [ebp-136], eax
	mov	eax, DWORD PTR [ebp-156]
	mov	DWORD PTR [ebp-132], eax
	mov	eax, DWORD PTR [ebp-152]
	mov	DWORD PTR [ebp-128], eax
	mov	DWORD PTR [ebp-124], 1
	mov	DWORD PTR [ebp-120], 2
	mov	DWORD PTR [ebp-116], 3
	mov	DWORD PTR [ebp-112], 4
	mov	DWORD PTR [ebp-108], 5
	mov	DWORD PTR [ebp-104], 1
	mov	DWORD PTR [ebp-100], 2
	mov	DWORD PTR [ebp-96], 3
	mov	DWORD PTR [ebp-92], 4
	mov	DWORD PTR [ebp-88], 5
	mov	DWORD PTR [ebp-84], 1
	mov	DWORD PTR [ebp-80], 2
	mov	DWORD PTR [ebp-76], 3
	mov	DWORD PTR [ebp-72], 4
	mov	DWORD PTR [ebp-68], 5
	mov	eax, DWORD PTR [ebp-124]
	mov	DWORD PTR [ebp-64], eax
	mov	eax, DWORD PTR [ebp-120]
	mov	DWORD PTR [ebp-60], eax
	mov	eax, DWORD PTR [ebp-116]
	mov	DWORD PTR [ebp-56], eax
	mov	eax, DWORD PTR [ebp-112]
	mov	DWORD PTR [ebp-52], eax
	mov	eax, DWORD PTR [ebp-108]
	mov	DWORD PTR [ebp-48], eax
	mov	eax, DWORD PTR [ebp-104]
	mov	DWORD PTR [ebp-44], eax
	mov	eax, DWORD PTR [ebp-100]
	mov	DWORD PTR [ebp-40], eax
	mov	eax, DWORD PTR [ebp-96]
	mov	DWORD PTR [ebp-36], eax
	mov	eax, DWORD PTR [ebp-92]
	mov	DWORD PTR [ebp-32], eax
	mov	eax, DWORD PTR [ebp-88]
	mov	DWORD PTR [ebp-28], eax
	mov	eax, DWORD PTR [ebp-84]
	mov	DWORD PTR [ebp-24], eax
	mov	eax, DWORD PTR [ebp-80]
	mov	DWORD PTR [ebp-20], eax
	mov	eax, DWORD PTR [ebp-76]
	mov	DWORD PTR [ebp-16], eax
	mov	eax, DWORD PTR [ebp-72]
	mov	DWORD PTR [ebp-12], eax
	mov	eax, DWORD PTR [ebp-68]
	mov	DWORD PTR [ebp-8], eax
	lea	eax, [ebp-148]
	mov	DWORD PTR [ebp-4], eax
	lea	eax, [ebp-64]
	mov	DWORD PTR b_object, eax
	mov	DWORD PTR [ebp-180], 1
	mov	eax, DWORD PTR b_object
	mov	ecx, DWORD PTR [eax+60]
	mov	edx, DWORD PTR [ebp-180]
	mov	eax, edx
	add	eax, eax
	add	eax, edx
	sal	eax, 2
	add	eax, ecx
	mov	DWORD PTR frame_c, eax
	mov	eax, DWORD PTR frame_c
	mov	eax, DWORD PTR [eax+8]
	mov	DWORD PTR [ebp-176], eax
	mov	eax, 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
