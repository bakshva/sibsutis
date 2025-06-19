#include "console.h"
#include "mySimpleComputer.h"
#include <stdio.h>
void printCommand()
{
    int address;
    sc_icounterGet(&address);

    mt_gotoXY(91, 5);
    if (address > 127) {
        printf("! + FF : FF");
        fflush(stdout);
        return;
    }

    int value;
    int sign;
    int command;
    int opperand;
    sc_memoryGet(address, &value);
    sc_commandDecode(value, &sign, &command, &opperand);
    char buffer[50];
    snprintf(
            buffer,
            sizeof(buffer),
            "%c %0*X : %0*X",
            (sign == 0) ? '+' : '-',
            2,
            command,
            2,
            opperand);
    printf("%s", buffer);
    fflush(stdout);
}