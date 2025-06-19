#include "register.h"

int sc_accumulatorSet(int value)
{
    if (value < -16384 || value > 16383) {
        return -1;
    }
    accumulator.var = value;
    return 0;
}