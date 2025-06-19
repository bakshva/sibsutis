#include "assembler.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

int Validate(Instruction inst)
{
    if (inst.address < 0 || inst.address > 127) {
        return -1;
    }

    char commandIsValid = 0;
    for (int i = 0; i != (sizeof(validsCommands) / sizeof(validsCommands[1]));
         i++) {
        if (strcmp(inst.command, validsCommands[i].commandName) == 0) {
            commandIsValid = 1;
            break;
        }
    }
    if (commandIsValid == 0) {
        printf("%s", inst.command);
        return -1;
    }

    char argIsValid = 0;
    if (inst.command[0] == '=') {
        if ((inst.arg[0] == '+' || inst.arg[0] == '-') && isxdigit(inst.arg[1])
            && isxdigit(inst.arg[2]) && isxdigit(inst.arg[3])
            && isxdigit(inst.arg[4]) && inst.arg[5] == '\0') {
            if (inst.arg[1] <= '7' && inst.arg[3] <= '7') {
                argIsValid = 1;
            }
        }
    } else {
        if (isxdigit(inst.arg[0]) && isxdigit(inst.arg[1])
            && inst.arg[2] == '\0') {
            if (strtol(inst.arg, NULL, 16) >= 0
                && strtol(inst.arg, NULL, 16) <= 127) {
                argIsValid = 1;
            }
        }
    }

    if (argIsValid == 0) {
        return -1;
    }
    return 0;
}