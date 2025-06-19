#include "register.h"

int sc_regGet(int reg, int* value)
{
    if (reg == REGISTER_OVERFLOW) {
        *value = flagsRegister & 0x1;
        return 0;
    } else if (reg == REGISTER_DIVIZION_ZERO) {
        *value = (flagsRegister >> 1) & 0x1;
        return 0;
    } else if (reg == REGISTER_MEMORY_OUT) {
        *value = (flagsRegister >> 2) & 0x1;
        return 0;
    } else if (reg == REGISTER_IGNORE_TACT) {
        *value = (flagsRegister >> 3) & 0x1;
        return 0;
    } else if (reg == REGISTER_INCORRECT_COMMAND) {
        *value = (flagsRegister >> 4) & 0x1;
        return 0;
    }
    return -1;
}