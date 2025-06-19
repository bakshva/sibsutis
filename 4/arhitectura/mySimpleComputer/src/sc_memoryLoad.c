#include "mem.h"
#include <stdio.h>
#include <string.h>

int sc_memoryLoad(char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;
    }
    int_15bit buffer[memorySize];
    int readSuccess = fread(buffer, sizeof(int_15bit), memorySize, file);
    if (readSuccess != memorySize) {
        return -1;
    }
    memcpy(memory, buffer, sizeof(buffer));
    fclose(file);
    return 0;
}