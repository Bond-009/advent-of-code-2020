#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

#define INPUT_LEN 200
#define SEARCH 2020

int inner_repair_avx(int i, const int *arr, __m256i search)
{
    __m256i start = _mm256_set1_epi32(i);
    for (int k = 0; k < INPUT_LEN; k += 8) {
        __m256i new = _mm256_loadu_si256((__m256i *)(&arr[k]));
        new = _mm256_add_epi32(start, new);
        int mask = _mm256_movemask_epi8(_mm256_cmpeq_epi32(new, search));
        if (mask == 0) {
            continue;
        }

        for (int l = 0; l < 8; l++) {
            if (mask & (0xf << (l * 4))) {
                return arr[k + l];
            }
        }
    }

    return 0;
}

int repair_avx(const int *arr)
{
    __m256i search = _mm256_set1_epi32(SEARCH);
    for (int i = 0; i < INPUT_LEN; i++) {
        __m256i start = _mm256_set1_epi32(arr[i]);
        for (int j = 0; j < INPUT_LEN; j += 8) {
            __m256i new = _mm256_loadu_si256((__m256i *)(&arr[j]));
            new = _mm256_add_epi32(start, new);
            int mask = _mm256_movemask_epi8(_mm256_cmpgt_epi32(new, search));
            if (mask == 0xffffffff) {
                continue;
            }

            switch (__lzcnt32(mask) / 4) {
                case 0: goto label0;
                case 1: goto label1;
                case 2: goto label2;
                case 3: goto label3;
                case 4: goto label4;
                case 5: goto label5;
                case 6: goto label6;
                case 7: goto label7;
            }

        label0:
            if ((mask & 0x0000000f) == 0) {
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 0), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j];
                }
            }

        label1:
            if ((mask & 0x000000f0) == 0) {
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 1), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j + 1];
                }
            }

        label2:
            if ((mask & 0x00000f00) == 0) {
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 2), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j + 2];
                }
            }

        label3:
            if ((mask & 0x0000f000) == 0) {
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 3), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j + 3];
                }
            }

        label4:
            if ((mask & 0x000f0000) == 0) {
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 4), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j + 4];
                }
            }

        label5:
            if ((mask & 0x00f00000) == 0 ){
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 5), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j + 5];
                }
            }

        label6:
            if ((mask & 0x0f000000) == 0) {
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 6), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j + 6];
                }
            }

        label7:
            if ((mask & 0xf0000000) == 0) {
                int tmp = inner_repair_avx(_mm256_extract_epi32(new, 7), arr, search);
                if (tmp) {
                    return tmp * arr[i] * arr[j + 7];
                }
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[argc - 1], "r");
    if (!file) {
        return 1;
    }

    char buffer[8] = { 0 };
    int input[INPUT_LEN] = { 0 };
    for (int i = 0; i < 200; i++) {
        fgets(buffer, 8, file);
        input[i] = atoi(buffer);
    }

    fclose(file);

    printf("%i\n", repair_avx(input));
}
