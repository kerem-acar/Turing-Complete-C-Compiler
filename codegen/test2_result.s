.intel_syntax noprefix
.globl main2
main2:
    push rbp
    mov rbp, rsp
    mov eax, 0
    push rax
    mov eax, 1
    push rax
    mov eax, dword ptr [rbp - 16]
    mov dword ptr [rbp - 8], eax
    add rsp, 8
    mov eax, 2
    push rax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, dword ptr [rbp - 16]
    pop rcx
    add eax, ecx
    mov dword ptr [rbp - 8], eax
    add rsp, 8
    mov eax, dword ptr [rbp - 8]
    add rsp, 8
    mov rsp, rbp
    pop rbp
    ret
