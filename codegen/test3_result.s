.intel_syntax noprefix
.globl main3
main3:
    push rbp
    mov rbp, rsp
    mov eax, 3
    push rax
    mov eax, 4
    push rax
    mov eax, 2
    mov dword ptr [rbp - 8], eax
    pop rcx
    add eax, ecx
    push rax
    mov eax, dword ptr [rbp - 16]
    mov rsp, rbp
    pop rbp
    ret
