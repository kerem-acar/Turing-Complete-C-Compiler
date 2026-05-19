.intel_syntax noprefix
.globl main1
main1:
    push rbp
    mov rbp, rsp
    mov eax, 0
    push rax
    mov eax, 0
    push rax
clause1:
    mov eax, dword ptr [rbp - 16]
    push rax
    mov eax, 10
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setl al
    cmp eax, 0
    je end1
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 4
    pop rcx
    sub ecx, eax
    mov eax, ecx
    cmp eax, 0
    mov eax, 0
    sete al
    cmp eax, 0
    je clause4
    jmp special1
    add rsp, 0
    jmp end4
clause4:
    jmp end4
end4:
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 1
    pop rcx
    add eax, ecx
    mov dword ptr [rbp - 8], eax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, 10
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setg al
    cmp eax, 0
    je clause5
    jmp end1
    add rsp, 0
    jmp end5
clause5:
    jmp end5
end5:
    add rsp, 0
special1:
    mov eax, dword ptr [rbp - 16]
    push rax
    mov eax, 1
    pop rcx
    add eax, ecx
    mov dword ptr [rbp - 16], eax
    jmp clause1
end1:
    add rsp, 8
    mov eax, dword ptr [rbp - 8]
    add rsp, 8
    mov rsp, rbp
    pop rbp
    ret
