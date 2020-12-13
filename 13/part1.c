#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int solve(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[200] = { 0 };
    fgets(buffer, 200, file);
    int h = atoi(buffer);
    fgets(buffer, 200, file);

    

    fclose(file);

    return abs(ver) + abs(hor);
}

int main(int argc, char *argv[])
{
    printf("%i\n", solve(argv[argc - 1]));
}
