section .text
global test_root_0_asm
test_root_0_asm:
    push ebp
    mov ebp, esp
;---prolog------------
    mov eax, 0
;---epilog------------
    leave
    ret