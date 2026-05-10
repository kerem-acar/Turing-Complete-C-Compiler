.intel_syntax noprefix
.globl main1
main1:
    push rbp
    mov rbp, rsp
    mov eax, 0
    push rax
    mov eax, 1
    push rax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, dword ptr [rbp - 16]
    pop rcx
    add eax, ecx
    cmp eax, 0
    je clause1
    mov eax, 3
    jmp end1
clause1:
    mov eax, 2
    jmp end1
end1:
    mov rsp, rbp
    pop rbp
    ret
