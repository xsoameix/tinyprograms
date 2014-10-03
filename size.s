.intel_syntax noprefix
.text
mov byte ptr [rax],cl
mov byte ptr [rax],ch
mov word ptr [rax],cx
mov dword ptr [rax],ecx
mov qword ptr [rax],rcx
mov qword ptr [rsp],rbp

mov al,cl
mov ah,ch
mov ax,cx
mov eax,ecx
mov rax,rcx
mov rsp,rbp
