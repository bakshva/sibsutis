#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>

void printAccumulator(void)
{
    mt_gotoXY(64, 2);

    int value = 0;
    sc_accumulatorGet(&value);

    int sign;
    int command;
    int opperand;
    sc_commandDecode(value, &sign, &command, &opperand);

    printf("sc: ");
    if (sign == 0) {
        putchar('+');
    } else {
        putchar('-');
    }
    printf("%0*X%0*X hex: %0*X", 2, command, 2, opperand, 4, value & 0x7FFF);
    fflush(stdout);
}