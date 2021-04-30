section .text
global test_root_0
test_root_0:
    push ebp
    mov ebp, esp
;---prolog------------
    mov eax, 0
;---epilog------------
    leave
    ret