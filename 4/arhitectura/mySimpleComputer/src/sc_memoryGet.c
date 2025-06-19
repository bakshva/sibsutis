#include "mem.h"

int sc_memoryGet(int address, int* value)
{
    if (address < 0 || address >= memorySize) {
        return -1;
    }
    *value = memory[address].var;
    return 0;
}