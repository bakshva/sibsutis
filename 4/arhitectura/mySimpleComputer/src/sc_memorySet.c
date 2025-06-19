#include "mem.h"

int sc_memorySet(int address, int value)
{
    if (address < 0 || address >= memorySize) {
        return -1;
    }
    if (value < -16384 || value > 16383) {
        return -1;
    }
    memory[address].var = value;
    return 0;
}