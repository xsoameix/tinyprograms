itor:
　　push ebp
　　mov  ebp, esp
　　mov  eax, dword ptr [ebp+8]
　　push eax
　　call isdone
　　leave
　　ret
main:
　　mov  eax, offset itor
　　push eax
　　mov  eax, dword ptr a
　　push eax
　　call all
