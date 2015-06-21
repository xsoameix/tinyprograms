# i++
5b:	8b 45 d8             	mov    -0x28(%rbp),%eax
5e:	8d 50 01             	lea    0x1(%rax),%edx
61:	89 55 d8             	mov    %edx,-0x28(%rbp)
# s[i++]
64:	48 63 d0             	movslq %eax,%rdx
67:	0f b6 7c 15 e0       	movzbl -0x20(%rbp,%rdx,1),%edi
# l-i-2
6c:	8b 55 d8             	mov    -0x28(%rbp),%edx
6f:	8b 4d dc             	mov    -0x24(%rbp),%ecx
72:	29 d1                	sub    %edx,%ecx
74:	89 ca                	mov    %ecx,%edx
76:	83 ea 02             	sub    $0x2,%edx
# l-i-2
79:	8b 4d d8             	mov    -0x28(%rbp),%ecx
7c:	8b 75 dc             	mov    -0x24(%rbp),%esi
7f:	29 ce                	sub    %ecx,%esi
81:	89 f1                	mov    %esi,%ecx
83:	83 e9 02             	sub    $0x2,%ecx
# s[l-i-2]
86:	48 63 c9             	movslq %ecx,%rcx
89:	44 0f b6 44 0d e0    	movzbl -0x20(%rbp,%rcx,1),%r8d
# s[i]
8f:	8b 4d d8             	mov    -0x28(%rbp),%ecx
92:	48 63 c9             	movslq %ecx,%rcx
95:	0f b6 74 0d e0       	movzbl -0x20(%rbp,%rcx,1),%esi
# s[l-i-2]
9a:	8b 4d d8             	mov    -0x28(%rbp),%ecx
9d:	44 8b 4d dc          	mov    -0x24(%rbp),%r9d
a1:	41 29 c9             	sub    %ecx,%r9d
a4:	44 89 c9             	mov    %r9d,%ecx
a7:	83 e9 02             	sub    $0x2,%ecx
aa:	48 63 c9             	movslq %ecx,%rcx
ad:	0f b6 4c 0d e0       	movzbl -0x20(%rbp,%rcx,1),%ecx
# s[i] ^ s[l-i-2]
b2:	31 ce                	xor    %ecx,%esi
# s[i] ^= s[l-i-2]
b4:	8b 4d d8             	mov    -0x28(%rbp),%ecx
b7:	48 63 c9             	movslq %ecx,%rcx
ba:	40 88 74 0d e0       	mov    %sil,-0x21(%rbp,%rcx,1)
# s[l-i-2] ^= s[i]
bf:	8b 4d d8             	mov    -0x28(%rbp),%ecx
c2:	48 63 c9             	movslq %ecx,%rcx
c5:	0f b6 4c 0d e0       	movzbl -0x20(%rbp,%rcx,1),%ecx
ca:	44 89 c6             	mov    %r8d,%esi
cd:	31 ce                	xor    %ecx,%esi
cf:	48 63 ca             	movslq %edx,%rcx
d2:	40 88 74 0d e0       	mov    %sil,-0x20(%rbp,%rcx,1)
# s[i++] ^= s[l-i-2]
d7:	48 63 d2             	movslq %edx,%rdx
da:	0f b6 54 15 e0       	movzbl -0x20(%rbp,%rdx,1),%edx
df:	31 fa                	xor    %edi,%edx
e1:	48 98                	cltq   
e3:	88 54 05 e0          	mov    %dl,-0x20(%rbp,%rax,1)

e7:	8b 45 dc             	mov    -0x24(%rbp),%eax
ea:	89 c2                	mov    %eax,%edx
ec:	c1 ea 1f             	shr    $0x1f,%edx
ef:	01 d0                	add    %edx,%eax
f1:	d1 f8                	sar    %eax
f3:	83 e8 01             	sub    $0x1,%eax
f6:	3b 45 d8             	cmp    -0x28(%rbp),%eax
f9:	0f 8f 48 ff ff ff    	jg     47 <main+0x47>
