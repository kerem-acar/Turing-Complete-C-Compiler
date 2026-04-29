.intel_syntax noprefix
.globl main2
main2:
    mov eax, 1
    push rax
    mov eax, 0
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setge al
    cmp eax, 0
    je clause1
    mov eax, 1
    jmp end1
clause1:
    mov eax, 2
    push rax
    mov eax, 8
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setle al
    cmp eax, 0
    mov eax, 0
    setne al
end1:
    ret
