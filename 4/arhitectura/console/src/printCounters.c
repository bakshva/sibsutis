#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>

void printCounters(void)
{
    mt_gotoXY(63, 5);

    int value, value2;
    int sign;
    int command;
    int opperand;
    sc_icounterGet(&value);
    sc_ignorerGet(&value2);
    sc_commandDecode(value, &sign, &command, &opperand);

    printf(" T: %0*d     IC: %c%0*X%0*X",
           2,
           value2,
           (sign == 0) ? '+' : '-',
           2,
           command,
           2,
           opperand);

    fflush(stdout);
}