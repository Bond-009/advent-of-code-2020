#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_INPUT_LEN 128

void insert_value_sorted(int *list, size_t *size, int value)
{
    long long low = 0, high = *size;
    while (low < high) {
        int m = low + (high - low) / 2;
        if (list[m] == value) {
            /* Name already exists,
                return pointer to the already existsing string and free the new one.
            */
            return;
        }
        else if (list[m] < value) {
            low = m + 1;
        }
        else {
            high = m;
        }
    }

    for (long long i = *size - 1; i >= low; i--) {
        list[i + 1] = list[i];
    }

    (*size)++;
    list[low] = value;
}

uint64_t pos_seq(int *input, size_t input_size)
{
    const static int TRIB[] = { 1, 1, 2, 4, 7 };
    int con = 0;
    uint64_t res = 1;

    for (size_t i = 1; i < input_size; i++)
    {
        int diff = input[i] - input[i - 1];
        if (diff == 1) {
            con++;
        }
        else {
            res *= TRIB[con];
            con = 0;
        }
    }

    return res;
}

size_t bags_count(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[16] = { 0 };

    int input[MAX_INPUT_LEN] = { 0 };
    size_t input_size = 1; // 0 is our start value

    while (fgets(buffer, 16, file)) {
        insert_value_sorted(input, &input_size, atoi(buffer));
    }

    // Add our device's built-in joltage adapter
    insert_value_sorted(input, &input_size, input[input_size - 1] + 3);

    fclose(file);

    return pos_seq(input, input_size);
}

int main(int argc, char *argv[])
{
    printf("%zu\n", bags_count(argv[argc - 1]));
}
