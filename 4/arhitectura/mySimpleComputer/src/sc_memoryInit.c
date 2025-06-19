#include "mem.h"

int sc_memoryInit(void)
{
    for (int i = 0; i != memorySize; i++) {
        memory[i].var = 0;
    }

    return 0;
}