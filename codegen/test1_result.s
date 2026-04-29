.intel_syntax noprefix
.globl main1
main1:
    mov eax, 1
    push rax
    mov eax, 3
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setl al
    cmp eax, 0
    jne clause1
    jmp end1
clause1:
    mov eax, 4
    push rax
    mov eax, 2
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setg al
    cmp eax, 0
    mov eax, 0
    setne al
end1:
    cmp eax, 0
    je clause2
    mov eax, 1
    jmp end2
clause2:
    mov eax, 1
    push rax
    mov eax, 2
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setne al
    cmp eax, 0
    mov eax, 0
    setne al
end2:
    ret
