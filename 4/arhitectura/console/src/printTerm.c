#include "cache.h"
#include "myReadKey.h"
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>

char INOUT[5][15] = {"", "", "", "", ""};

int printTerm(int address, int input) // input = 0 вывод иначе ввод
{
    for (int i = 0; i != 4; i++) {
        snprintf(INOUT[i], sizeof(INOUT[i]), "%s", INOUT[i + 1]);
    }
    int start_X = 67;
    int start_Y = 20;
    mt_gotoXY(start_X, start_Y);
    for (int i = 0; i != 4; i++) {
        printf("%s", INOUT[i]);
        fflush(stdout);
        start_Y++;
        mt_gotoXY(start_X, start_Y);
    }
    fflush(stdout);
    mt_gotoXY(67, 24);
    printf("         ");
    fflush(stdout);
    mt_gotoXY(67, 24);
    char buffer[10];
    printf("%0*X%c ", 2, address, (input == 0) ? '>' : '<');
    fflush(stdout);
    int sign;
    int command;
    int opperand;
    int value;

    int tacts;
    if (input == 1) {
        mt_gotoXY(71, 24);
        while (rk_readvalue(&value)) {
        }
        tacts = sc_memoryControllerSet(address, value);
    } else {
        tacts = sc_memoryControllerGet(address, &value);
    }

    sc_commandDecode(value, &sign, &command, &opperand);

    if (input == 0) {
        printf("%c%0*X%0*X", (sign == 0) ? '+' : '-', 2, command, 2, opperand);
    }
    fflush(stdout);
    snprintf(
            buffer,
            sizeof(buffer),
            "%0*X%c %c%0*X%0*X",
            2,
            address,
            (input == 0) ? '>' : '<',
            (sign == 0) ? '+' : '-',
            2,
            command,
            2,
            opperand);

    snprintf(INOUT[5 - 1], sizeof(INOUT[5 - 1]), "%s", buffer);
    return tacts;
}