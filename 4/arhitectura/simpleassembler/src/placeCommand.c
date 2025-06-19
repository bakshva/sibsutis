#include "assembler.h"
#include "mySimpleComputer.h"
#include <stdio.h>
#include <string.h>

int placeCommand(Instruction* inst)
{
    if (Validate(*inst)) {
        return -1;
    }

    for (int i = 0; i != (sizeof(validsCommands) / sizeof(validsCommands[1]));
         i++) {
        if (strcmp(inst->command, validsCommands[i].commandName) == 0) {
            inst->commandVal = validsCommands[i].command;
            break;
        }
    }

    if (inst->command[0] == '=') {
        int sign = (inst->arg[0] == '+') ? 0 : 1;
        int command;
        int opperand;
        int value;
        sscanf(inst->arg + 1, "%2X%2X", &command, &opperand);
        sc_commandEncode(sign, command, opperand, &value);
        inst->argVal = value;
        sc_memorySet(inst->address, inst->argVal);
    } else {
        sscanf(inst->arg, "%2X", &(inst->argVal));
        int sign = 0, command = inst->commandVal, opperand = inst->argVal;
        int value;
        sc_commandEncode(sign, command, opperand, &value);
        sc_memorySet(inst->address, value);
    }
    return 0;
}