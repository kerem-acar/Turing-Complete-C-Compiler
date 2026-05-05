.intel_syntax noprefix
.globl main2
main2:
    push rbp
    mov rbp, rsp
    mov eax, 0
    push rax
    mov eax, 4
    mov dword ptr [rbp - 8], eax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 3
    pop rcx
    add eax, ecx
    mov rsp, rbp
    pop rbp
    ret
