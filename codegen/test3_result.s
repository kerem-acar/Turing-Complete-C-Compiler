.intel_syntax noprefix
.globl main3
main3:
    push rbp
    mov rbp, rsp
    mov eax, 0
    push rax
    mov eax, 1
    cmp eax, 0
    je clause1
    mov eax, 2
    jmp end1
clause1:
    mov eax, 3
    jmp end1
end1:
    mov dword ptr [rbp - 8], eax
    mov eax, dword ptr [rbp - 8]
    mov rsp, rbp
    pop rbp
    ret
