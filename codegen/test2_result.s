.intel_syntax noprefix
.globl main2
main2:
    push rbp
    mov rbp, rsp
    mov eax, 1
    push rax
clause1:
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 2
    pop rcx
    imul eax, ecx
    mov dword ptr [rbp - 8], eax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 2
    pop rcx
    sub ecx, eax
    mov eax, ecx
    cmp eax, 0
    mov eax, 0
    sete al
    cmp eax, 0
    je clause2
    jmp end1
    add rsp, 0
    jmp end2
clause2:
    jmp end2
end2:
    add rsp, 0
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 11
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setl al
    cmp eax, 0
    je end1
special1:
    jmp clause1
end1:
    mov eax, dword ptr [rbp - 8]
    add rsp, 8
    mov rsp, rbp
    pop rbp
    ret
