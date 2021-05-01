section .data
    TWO         dt 2.0
    THREE       dt 3.0
    CONST_1     dt 0.35
    CONST_2     dt -0.95
    CONST_3     dt 2.7

section .text

GLOBAL f1
GLOBAL f2
GLOBAL f3

f1:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fld tword[CONST_3]  ; 2.7
    fld tword[CONST_2]  ; 2.7, -0.95
    fld tword[ebp + 8]  ; 2.7, -0.95, x
    fmul                ; 2.7, -0.95x
    fld tword[ebp + 8]  ; 2.7, -0.95x, x
    fld tword[ebp + 8]  ; 2.7, -0.95x, x, x
    fmul                ; 2.7, -0.95x, x^2
    fld tword[CONST_1]  ; 2.7, -0.95x, x^2, 0.35
    fmul                ; 2.7, -0.95x, 0.35x^2
    fadd                ; 2.7, 0.35x^2 - 0.95x
    faddp               ; 0.35x^2 - 0.95x + 2.7
    fstp
;---epilog------------
    leave
    ret

f2:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fld1                ; 1
    fld tword[ebp + 8]  ; 1, x
    fld tword[THREE]    ; 1, x, 3
    fmul                ; 1, 3x
    faddp               ; 1 + 3x
;---epilog------------
    leave
    ret

f3:
    push ebp
    mov ebp, esp
;---prolog------------
    finit
    fld1                ; 1
    fld tword[ebp + 8]  ; 1, x
    fld tword[TWO]      ; 1, x, 2
    faddp               ; 1, x + 2
    fdivp               ; 1 / (x + 2)
;---epilog------------
    leave
    ret