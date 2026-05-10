.intel_syntax noprefix
.globl main2
main2:
    push rbp
    mov rbp, rsp
    mov eax, 2
    push rax
    mov eax, 3
    push rax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, dword ptr [rbp - 16]
    pop rcx
    add eax, ecx
    cmp eax, 0
    je clause1
    mov eax, 1
    jmp end1
clause1:
    mov eax, dword ptr [rbp - 16]
    push rax
    mov eax, dword ptr [rbp - 8]
    pop rcx
    sub ecx, eax
    mov eax, ecx
    cmp eax, 0
    je clause3
    mov eax, 4
    jmp end3
clause3:
    mov eax, 0
    jmp end3
end3:
    jmp end1
end1:
    mov rsp, rbp
    pop rbp
    ret
