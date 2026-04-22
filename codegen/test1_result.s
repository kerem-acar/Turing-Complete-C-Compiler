.intel_syntax noprefix
.globl main1
main1:
    mov eax, 3
    push rax
    mov eax, 4
    push rax
    mov eax, 5
    pop rcx
    add eax, ecx
    pop rcx
    add eax, ecx
    ret
