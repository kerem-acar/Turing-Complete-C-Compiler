.intel_syntax noprefix
.globl main3
main3:
    mov eax, 3
    push rax
    mov eax, 10
    pop rcx
    cmp ecx, eax
    mov eax, 0
    sete al
    cmp eax, 0
    je clause1
    mov eax, 1
    jmp end
clause1:
    mov eax, 9
    push rax
    mov eax, 11
    pop rcx
    cmp ecx, eax
    mov eax, 0
    setne al
    cmp eax, 0
    mov eax, 0
    setne al
end:
    ret
