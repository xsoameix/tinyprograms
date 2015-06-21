#include <stdio.h>

void * foo = &foo;

int
main(int a) {
  printf("%p\n", foo);
  printf("%p\n", main);
}
/*
   0: 55                    push   %rbp
   1:  48 89 e5              mov    %rsp,%rbp
   4: bf 00 00 00 00        mov    $0x0,%edi
   9:  e8 00 00 00 00        callq  e <main+0xe>
   e: 5d                    pop    %rbp
   f:  c3                    retq
*/
/*char main[] = "\xe8";*/
/*
	.file	"binary-main.c"
	.section	.rodata
.LC0:
	.string	"hello world"
	.text
	.globl	main
	.type	main, @function
main:
    movq    %rax
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$.LC0, %edi
	call	puts
	popq	%rbp
	ret
  */
