global repair_avx_inner

section .text

repair_avx_inner:
;    vpbroadcastd    ymm1, edi                 ; AVX512VL AVX512F
    vmovd           xmm1, edi
    vpbroadcastd    ymm1, xmm1
    vpsubd          ymm1, ymm0, ymm1
%rep    24
    vpcmpeqd        ymm2, ymm1, [rsi]
    vpmovmskb       edx, ymm2
    test            edx, edx
    jne             .found
    add             rsi, 32                 ; set up to read the next 256 bits (32 bytes) (8 * dword)
%endrep
    vpcmpeqd        ymm2, ymm1, [rsi]
    vpmovmskb       edx, ymm2
    test            edx, edx
    jne             .found
    xor             eax, eax                ; not found, return 0
    vzeroupper                              ; eliminate performance penalties caused by false dependencies when transitioning between AVX and legacy SSE instructions
    ret
.found:
    bsf             edx, edx
    mov             eax, dword [rsi + rdx]
    vzeroupper                              ; eliminate performance penalties caused by false dependencies when transitioning between AVX and legacy SSE instructions
    ret
