.intel_syntax noprefix
.globl main3
main3:
    mov eax, 6
    push rax
    mov eax, 3
    push rax
    mov eax, 2
    pop rcx
    imul eax, ecx
    mov ecx, eax
    pop rax
    cdq
    idiv ecx
    ret
