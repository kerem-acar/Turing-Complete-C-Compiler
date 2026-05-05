.intel_syntax noprefix
.globl main1
main1:
    push rbp
    mov rbp, rsp
    mov eax, 3
    push rax
    mov eax, dword ptr [rbp - 8]
    mov rsp, rbp
    pop rbp
    ret
