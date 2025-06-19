#include "myTerm.h"
#include "mytype.h"
#include <stdio.h>

void printDecodedCommand(int value)
{
    mt_gotoXY(2, 17);
    printf("dec: ");
    fflush(stdout);
    if (value < 0) {
        mt_gotoXY(6, 17);
        printf("-");
        fflush(stdout);
    }

    printf("%0*d | oct: %0*o | hex: %0*X | bin: ",
           5,
           (value < 0) ? -1 * value : value,
           5,
           value & 0x7FFF,
           4,
           value & 0x7FFF);
    for (int i = 15 - 1; i >= 0; i--) {
        putchar((value >> i) & 1 ? '1' : '0');
    }
    fflush(stdout);
}
