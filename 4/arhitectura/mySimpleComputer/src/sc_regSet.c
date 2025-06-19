#include "register.h"

int sc_regSet(int reg, int value)
{
    if ((reg & 0xFFFE) == 0) {
        if (value == 0) {
            flagsRegister = flagsRegister & ~1;
        } else {
            flagsRegister = flagsRegister | 1;
        }
        return 0;
    } else if ((reg & 0xFFFD) == 0) {
        if (value == 0) {
            flagsRegister = flagsRegister & ~(1 << 1);
        } else {
            flagsRegister = flagsRegister | (1 << 1);
        }
        return 0;
    } else if ((reg & 0xFFFB) == 0) {
        if (value == 0) {
            flagsRegister = flagsRegister & ~(1 << 2);
        } else {
            flagsRegister = flagsRegister | (1 << 2);
        }
        return 0;
    } else if ((reg & 0xFFF7) == 0) {
        if (value == 0) {
            flagsRegister = flagsRegister & ~(1 << 3);
        } else {
            flagsRegister = flagsRegister | (1 << 3);
        }
        return 0;
    } else if ((reg & 0xFFEF) == 0) {
        if (value == 0) {
            flagsRegister = flagsRegister & ~(1 << 4);
        } else {
            flagsRegister = flagsRegister | (1 << 4);
        }
        return 0;
    }
    return -1;
}