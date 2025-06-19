#include "mem.h"
#include <stdio.h>

int sc_memorySave(char* filename)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return -1;
    }
    int writeSuccess = fwrite(memory, sizeof(int_15bit), memorySize, file);
    if (writeSuccess != memorySize) {
        return -1;
    }
    fclose(file);
    return 0;
}