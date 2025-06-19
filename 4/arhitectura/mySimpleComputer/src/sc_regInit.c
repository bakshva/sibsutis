#include "register.h"

int sc_regInit(void)
{
    flagsRegister = REGISTER_IGNORE_TACT;
    return 0;
}