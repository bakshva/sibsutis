#include "mytype.h"
#include <stdio.h>

int sc_commandDecode(int value, int* sign, int* command, int* opperand)
{
    if (sign == NULL || command == NULL || opperand == NULL) {
        return -1;
    }
    *opperand = value & 0x7F;
    value = value >> 7;
    *command = value & 0x7F;
    value = value >> 7;
    *sign = value & 0x1;
    return 0;
}