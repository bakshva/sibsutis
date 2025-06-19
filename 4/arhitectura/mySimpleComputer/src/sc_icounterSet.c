#include "register.h"

int sc_icounerSet(int value)
{
    if (value < -16384 || value > 16383) {
        return -1;
    }
    commandCounter.var = value;
    return 0;
}