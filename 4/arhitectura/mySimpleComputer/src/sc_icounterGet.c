#include "register.h"
#include <stdio.h>

int sc_icounterGet(int* value)
{
    if (value == NULL) {
        return -1;
    }
    *value = commandCounter.var;
    return 0;
}