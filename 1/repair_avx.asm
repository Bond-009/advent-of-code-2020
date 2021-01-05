global repair_avx_inner

section .text

repair_avx_inner:
;    vpbroadcastd    ymm1, edi                 ; AVX512VL AVX512F
    vmovd           xmm1, edi
    vpbroadcastd    ymm1, xmm1
    vpsubd          ymm1, ymm0, ymm1
%assign i 0
%rep    25
    vpcmpeqd        ymm2, ymm1, [rsi + i]
    vpmovmskb       eax, ymm2
    test            eax, eax
    jne             .found
%assign i i+32
%endrep
    xor             eax, eax                ; not found, return 0
    vzeroupper                              ; eliminate performance penalties caused by false dependencies when transitioning between AVX and legacy SSE instructions
    ret
.found:
    vzeroupper                              ; eliminate performance penalties caused by false dependencies when transitioning between AVX and legacy SSE instructions
    movd            eax, xmm1
    ret
