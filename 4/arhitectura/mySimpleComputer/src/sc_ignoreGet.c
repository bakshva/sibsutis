#include "register.h"
#include <stdio.h>

int sc_ignorerGet(int* value)
{
    if (value == NULL) {
        return -1;
    }
    *value = commandIgnoreTacktCounter.var;
    return 0;
}