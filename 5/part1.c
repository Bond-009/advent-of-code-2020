#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLUMNS 8
#define ROWS 128

int get_seat_id(const char *seat)
{
    int row = 0;
    int row_lower = 0;
    int row_upper = ROWS - 1;
    int column = 0;
    int column_lower = 0;
    int column_upper = COLUMNS - 1;
    int i = 0;
    for (; i < 6; i++) {
        switch (seat[i]) {
            case 'F':
                row_upper -= (row_upper - row_lower + 1) / 2;
                break;
            case 'B':
                row_lower += (row_upper - row_lower + 1) / 2;
                break;
        }
    }

    switch (seat[i++]) {
        case 'F':
            row = row_lower;
            break;
        case 'B':
            row = row_upper;
            break;
    }

    for (; i < 9; i++) {
        switch (seat[i]) {
            case 'L':
                column_upper -= (column_upper - column_lower + 1) / 2;
                break;
            case 'R':
                column_lower += (column_upper - column_lower + 1) / 2;
                break;
        }
    }

    switch (seat[i++]) {
        case 'L':
            column = column_lower;
            break;
        case 'R':
            column = column_upper;
            break;
    }

    return row * COLUMNS + column;
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");

    // Include space for newline and string terminator
    char buffer[128] = { 0 };

    int max = 0;

    while (fgets(buffer, 128, file)) {
        int tmp = get_seat_id(buffer);
        if (tmp > max) {
            max = tmp;
        }
    }

    printf("%i\n", max);
}
