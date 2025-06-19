#include "register.h"

int sc_ignoreInit(void)
{
    commandIgnoreTacktCounter.var = 0;
    return 0;
}