#include "cache.h"
#include "commands.h"
#include "execValue.h"
#include "mySimpleComputer.h"

int ALU(int command, int operand)
{
    if (operand >= 128 || operand < 0) {
        return -1;
    }
    int pointAccumValue;
    int currentAccum, memoryCell;

    sc_accumulatorGet(&currentAccum);
    sc_memoryControllerGet(operand, &memoryCell);

    int result;
    switch (command) {
    case ADD:
        result = currentAccum + memoryCell;
        break;
    case SUB:
        result = currentAccum - memoryCell;
        break;
    case DIVIDE:
        if (memoryCell == 0) {
            sc_regSet(REGISTER_DIVIZION_ZERO, 1);
            sc_regSet(REGISTER_IGNORE_TACT, 1);
            is_execute = 0;
        }
        result = currentAccum / memoryCell;
        break;
    case MUL:
        result = currentAccum * memoryCell;
        break;
    case ADDC:
        if (currentAccum < 0 || currentAccum > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            sc_regSet(REGISTER_IGNORE_TACT, 1);
            is_execute = 0;
        }
        sc_memoryControllerGet(currentAccum, &pointAccumValue);
        sc_memoryControllerGet(operand, &memoryCell);
        break;
    case SUBC:
        if (currentAccum < 0 || currentAccum > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            sc_regSet(REGISTER_IGNORE_TACT, 1);
            is_execute = 0;
        }
        sc_memoryControllerGet(operand, &memoryCell);
        result = memoryCell - pointAccumValue;
        break;
    }
    if (result < -16384 || result > 16383) {
        sc_regSet(REGISTER_OVERFLOW, 1);
        is_execute = 0;
        return -1;
    }
    sc_accumulatorSet(result);
    return 0;
}