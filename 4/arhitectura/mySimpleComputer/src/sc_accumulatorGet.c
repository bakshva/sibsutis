#include "register.h"
#include <stdio.h>
int sc_accumulatorGet(int* value)
{
    if (value == NULL) {
        return -1;
    }
    *value = accumulator.var;
    return 0;
}