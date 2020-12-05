#include <stdio.h>

#define COLUMNS 8
#define ROWS 128

int get_seat_id(const char *seat)
{
    int end_res = 0;
    int i = 0;
    for (; i < 7; i++) {
        if (seat[i] == 'B') {
            end_res |= 0x200 >> i;
        }
    }

    for (; i < 10; i++) {
        if (seat[i] == 'R') {
            end_res |= 0x200 >> i;
        }
    }

    return end_res;
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");

    char table[COLUMNS * ROWS] = { 0 };

    // Include space for newline and string terminator
    char buffer[16] = { 0 };

    int min = __INT_MAX__;
    int max = 0;
    while (fgets(buffer, 16, file)) {
        int tmp = get_seat_id(buffer);
        if (tmp > max)
        {
            max = tmp;
        }

        if (tmp < min)
        {
            min = tmp;
        }

        table[tmp] = 1;
    }

    for (int i = min + 1; i < max; i++) {
        if (table[i] == 0) {
            printf("%i", i);
            break;
        }
    }
}
