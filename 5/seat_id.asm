global seat_id

section .data

section .text

seat_id:
    xor     eax, eax            ; set up return value
    cmp     BYTE [rdi], 66      ; B
    sete    al
    shl     eax, 1
    xor     ecx, ecx
    cmp     BYTE [rdi + 1], 66
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 2], 66
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 3], 66
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 4], 66
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 5], 66
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 6], 66
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 7], 82  ; R
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 8], 82
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 9], 82
    sete    cl
    or      eax, ecx
    ret
