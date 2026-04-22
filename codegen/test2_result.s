.intel_syntax noprefix
.globl main2
main2:
    mov eax, 2
    push rax
    mov eax, 3
    pop rcx
    add eax, ecx
    not eax
    push rax
    mov eax, 4
    pop rcx
    imul eax, ecx
    ret
