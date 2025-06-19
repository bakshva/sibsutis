#include "cache.h"
#include "commands.h"
#include "console.h"
#include "execValue.h"
#include "mySimpleComputer.h"
#include <stdio.h>

void CU(void)
{
    int sign;
    int command;
    int opperand;
    int value;
    int comandline;
    sc_icounterGet(&value);

    sc_memoryControllerGet(value, &comandline);

    sc_commandDecode(comandline, &sign, &command, &opperand);

    if (sign == 1) {
        sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
        sc_regSet(REGISTER_IGNORE_TACT, 1);
        is_execute = 0;
        return;
    }
    int tempVal;
    switch (command) {
    case READ:
        sc_regSet(REGISTER_IGNORE_TACT, 1);
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        printTerm(opperand, 1);
        sc_regSet(REGISTER_IGNORE_TACT, 0);
        printCell(opperand, WHITE, BLACK);
        sc_regSet(REGISTER_IGNORE_TACT, 0);
        break;
    case WRITE:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        printTerm(opperand, 0);
        break;
    case ADD:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        ALU(ADD, opperand);
        break;
    case SUB:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        ALU(SUB, opperand);
        break;
    case DIVIDE:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        ALU(DIVIDE, opperand);
        break;
    case MUL:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        ALU(MUL, opperand);
        break;
    case ADDC:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        ALU(ADDC, opperand);
        break;
    case SUBC:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        ALU(SUBC, opperand);
        break;
    case LOAD:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        sc_memoryControllerGet(opperand, &tempVal);
        sc_accumulatorSet(tempVal);
        break;
    case STORE:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        sc_accumulatorGet(&tempVal);
        sc_memoryControllerSet(opperand, tempVal);
        printCell(opperand, WHITE, BLACK);
        break;
    case JUMP:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        sc_icounerSet(opperand);
        return;
        break;
    case JNEG:
        if (opperand < 0 || opperand > 127) {
            is_execute = 0;
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            return;
        }
        sc_accumulatorGet(&tempVal);
        if (tempVal < 0) {
            sc_icounerSet(opperand);
            return;
        }
        break;
    case JZ:
        if (opperand < 0 || opperand > 127) {
            sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
            is_execute = 0;
            return;
        }
        sc_accumulatorGet(&tempVal);
        if (tempVal == 0) {
            sc_icounerSet(opperand);
            return;
        }
        break;
    case HALT:
        for (int i = 0; i != MAX_PAGES; i++) {
            sc_cacheLineFflush(cache[i].offset);
        }
        sc_regSet(REGISTER_IGNORE_TACT, 1);
        is_execute = 0;
        return;
        break;
    case NOP:
        break;
    case CPUINFO:
        mt_gotoXY(0, 26);
        printf("Нестеров Илья Борисович ИС-342");
        fflush(stdout);
        break;
    }
    printFlags();
    printAccumulator();
    printCounters();
    printCommand();
    if (value < 127 && value >= 0) {
        sc_icounerSet(value + 1);
    } else {
        for (int i = 0; i != MAX_PAGES; i++) {
            sc_cacheLineFflush(cache[i].offset);
        }
        is_execute = 0;
        sc_regSet(REGISTER_IGNORE_TACT, 1);
    }
}