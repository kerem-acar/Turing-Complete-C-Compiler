.intel_syntax noprefix
.globl main3
main3:
    push rbp
    mov rbp, rsp
    mov eax, 0
    push rax
    mov eax, 1
    push rax
clause1:
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 5
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setl al
    cmp eax, 0
    je end1
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 2
    pop rcx
    add eax, ecx
    mov dword ptr [rbp - 8], eax
    mov eax, dword ptr [rbp - 16]
    push rax
    mov eax, dword ptr [rbp - 8]
    pop rcx
    imul eax, ecx
    mov dword ptr [rbp - 16], eax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, dword ptr [rbp - 16]
    pop rcx
    sub ecx, eax
    mov eax, ecx
    cmp eax, 0
    mov eax, 0
    sete al
    cmp eax, 0
    je clause3
    jmp end1
    add rsp, 0
    jmp end3
clause3:
    jmp end3
end3:
    add rsp, 0
special1:
    jmp clause1
end1:
    mov eax, dword ptr [rbp - 8]
    add rsp, 16
    mov rsp, rbp
    pop rbp
    ret
