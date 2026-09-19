section .text
global _start
_start:
    mov eax, 123
    push eax
    mov eax, 456
    pop ebx
    add eax, ebx
    push eax
    mov eax, 6456
    pop ebx
    add eax, ebx
    push eax
    mov eax, 6
    pop ebx
    add eax, ebx
    ; Exit the program
    mov ebx, eax
    mov eax, 1
    int 0x80
