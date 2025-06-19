#include "register.h"

int sc_ignoreSet(int value)
{
    if (value < 0 || value > 127) {
        return -1;
    }
    commandIgnoreTacktCounter.var = value;
    return 0;
}
