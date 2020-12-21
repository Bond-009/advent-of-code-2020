global seat_id_sse3

section .data
    align 16
    xmm_cmp:    db 1, 'RBBBBBBB', 1, 1, 1, 1, 1, 1, 1
    xmm_shuf:   db 8, 7, 6, 5, 4, 3, 2, 1, 0, 9, 10, 11, 12, 13, 14, 15


section .text

seat_id_sse3:
    xor         eax, eax                ; set up return value
    movq        xmm0, qword [rdi]       ; load first 8 bytes
    pshufb      xmm0, [rel xmm_shuf]    ; reverse byte order and already shift left once
    pcmpeqb     xmm0, [rel xmm_cmp]
    pmovmskb    eax, xmm0               ; store mask in return value
    xor         ecx, ecx
    cmp         BYTE [rdi + 8], 'R'
    sete        cl
    or          eax, ecx
    shl         eax, 1
    cmp         BYTE [rdi + 9], 'R'
    sete        cl
    or          eax, ecx
    ret
