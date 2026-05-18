.intel_syntax noprefix
.globl main1
main1:
    push rbp
    mov rbp, rsp
    mov eax, 0
    push rax
    mov eax, dword ptr [rbp - 8]
    cmp eax, 0
    je clause1
    mov eax, 2
    push rax
    mov eax, dword ptr [rbp - 16]
    add rsp, 8
    jmp end1
clause1:
    mov eax, 3
    push rax
    mov eax, dword ptr [rbp - 8]
    push rax
    mov eax, dword ptr [rbp - 16]
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setl al
    cmp eax, 0
    je clause3
    mov eax, 4
    add rsp, 0
    jmp end3
clause3:
    mov eax, 5
    add rsp, 0
    jmp end3
end3:
    add rsp, 8
    jmp end1
end1:
    add rsp, 8
    mov rsp, rbp
    pop rbp
    ret
