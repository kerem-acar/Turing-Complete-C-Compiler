.intel_syntax noprefix
.globl main3
main3:
    push rbp
    mov rbp, rsp
    mov eax, 2
    push rax
    mov eax, 3
    mov dword ptr [rbp - 8], eax
    mov eax, 0
    push rax
    add rsp, 8
    mov eax, dword ptr [rbp - 8]
    add rsp, 8
    mov rsp, rbp
    pop rbp
    ret
