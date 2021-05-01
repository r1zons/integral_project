section .data
    MINUS       dt -1.0
    HALF        dt 0.5
    THREE       dt 3.0
    FOUR        dt 4.0
    SIX         dt 6.0

section .text

global test_root_0
global test_root_f1
global test_root_g1
global test_integral_func1
global test_integral_func2

test_root_0:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fldz
    fstp
;---epilog------------
    leave
    ret

test_root_f1:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fld tword[ebp + 8]
    fstp
;---epilog------------
    leave
    ret

test_root_g1:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fld tword[ebp + 8]
    fld tword[MINUS]
    fmulp
    fstp
;---epilog------------
    leave
    ret
    
; test_root_f2:
;     push ebp
;     mov ebp, esp
; ;---prolog------------
;     finit
;     fld tword[ebp + 8]
;     fstp
; ;---epilog------------
;     leave
;     ret

test_integral_func1:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fld tword[HALF]
    fld tword[ebp + 8]
    fld tword[ebp + 8]
    fmulp
    fmulp
    fld tword[SIX]
    fsubp
    fstp
;---epilog------------
    leave
    ret


test_integral_func2:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fld tword[THREE]
    fld tword[FOUR]
    fld tword[ebp + 8]
    fmulp
    faddp
    fstp
;---epilog------------
    leave
    ret