global seat_id

section .data

section .text

seat_id:
    xor     eax, eax            ; set up return value
    cmp     BYTE [rdi], 'B'
    sete    al
    shl     eax, 1
    xor     ecx, ecx
    cmp     BYTE [rdi + 1], 'B'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 2], 'B'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 3], 'B'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 4], 'B'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 5], 'B'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 6], 'B'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 7], 'R'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 8], 'R'
    sete    cl
    or      eax, ecx
    shl     eax, 1
    cmp     BYTE [rdi + 9], 'R'
    sete    cl
    or      eax, ecx
    ret
