#include "mySimpleComputer.h"
#include <basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialParam(FILE* file);

void codeGenInput(FILE* file, intermediateCode* inm);
void codeGenOutput(FILE* file, intermediateCode* inm);
int codeGenGoto(FILE* file, intermediateCode* inm);
int codeGenLeT(FILE* file, intermediateCode* inm);

int codeGenerator(FILE* file, intermediateCode* inm)
{
    initialParam(file);
    for (int i = 0; i != counCommands; i++) {
        if (inm[i].typeCmd == REM) {
            continue;
        } else if (inm[i].typeCmd == INPUT) {
            codeGenInput(file, &inm[i]);
        } else if (inm[i].typeCmd == OUTPUT) {
            codeGenOutput(file, &inm[i]);
        } else if (inm[i].typeCmd == GOTO) {
            if (codeGenGoto(file, &inm[i])) {
                return -1;
            }
        } else if (inm[i].typeCmd == LET) {
            if (codeGenLeT(file, &inm[i])) {
                return -1;
            }
        } else if (inm[i].typeCmd == END) {
            fprintf(file, "%02x HALT 00\n", inm[i].address);
        } else if (inm[i].typeCmd == IF) {
            int address = inm[i].address;
            int jumpaddr;
            int firstoppaddr = nameTableAddresGet(inm[i].loperator);
            int secondoppaddr = nameTableAddresGet(inm[i].roperator);
            fprintf(file, "%02x LOAD %02x\n", address, firstoppaddr);
            address++;
            fprintf(file, "%02x SUB %02x\n", address, secondoppaddr);
            switch (inm[i].typeCmd2) {
            case INPUT:
                jumpaddr = address + 1;
                break;
            case OUTPUT:
                jumpaddr = address + 1;
                break;
            case GOTO:
                jumpaddr = address + 1;
            case LET:
                jumpaddr = address + RpnCountOperations(&inm[i].RPM) + 1;
            }
            address++;
            if (inm[i].logOperator == '=') {
                jumpaddr++;
                fprintf(file, "%02x JZ %02x\n", address, address + 2);
                address++;
                fprintf(file, "%02x JUMP %02x\n", address, jumpaddr);
                address++;

            } else if (inm[i].logOperator == '>') {
                fprintf(file, "%02x JNEG %02x\n", address, jumpaddr);
                address++;
            } else if (inm[i].logOperator == '<') {
                jumpaddr++;
                fprintf(file, "%02x JNEG %02x\n", address, address + 2);
                address++;
                fprintf(file, "%02x JUMP %02x\n", address, jumpaddr);
                address++;
            }
            inm[i].address = address;
            switch (inm[i].typeCmd2) {
            case INPUT:
                codeGenInput(file, &inm[i]);
                break;
            case OUTPUT:
                codeGenOutput(file, &inm[i]);
                break;
            case GOTO:
                codeGenGoto(file, &inm[i]);
                break;
            case LET:
                codeGenLeT(file, &inm[i]);
                break;
            }
        }
    }
}

void codeGenInput(FILE* file, intermediateCode* inm)
{
    int opperatorAddress = nameTableAddresGet(inm->operator);
    fprintf(file, "%0*X READ %0*x\n", 2, inm->address, 2, opperatorAddress);
}

void codeGenOutput(FILE* file, intermediateCode* inm)
{
    int opperatorAddress = nameTableAddresGet(inm->operator);
    fprintf(file, "%0*X WRITE %0*x\n", 2, inm->address, 2, opperatorAddress);
}

int codeGenGoto(FILE* file, intermediateCode* inm)
{
    int lableGoto = lableTableGetAddress(inm->lable);
    if (lableGoto == -1) {
        return -1;
    }
    fprintf(file, "%0*X JUMP %0*x\n", 2, inm->address, 2, lableGoto);
    return 0;
}

int codeGenLeT(FILE* file, intermediateCode* inm)
{
    if (inm->RPM.tokenCount == 1) {
        int addrsrc = nameTableAddresGet(inm->RPM.token[0].value);
        int adddst = nameTableAddresGet(inm->operator);
        if (addrsrc < 0 || adddst < 0) {
            return -1;
        }
        fprintf(file, "%0*X LOAD %0*x\n", 2, inm->address, 2, addrsrc);
        fprintf(file, "%0*X STORE %0*x\n", 2, inm->address + 1, 2, adddst);
    } else {
        int commandaddr = inm->address;
        int stacksizeDopCells
                = nameTable.names[nameTable.namecount - 1].address;
        TOKENS stack;
        tokenInit(&stack);
        for (int j = 0; j != inm->RPM.tokenCount; j++) {
            if (inm->RPM.token[j].type == TOKENNAME) {
                tokenAdd(
                        &stack,
                        inm->RPM.token[j].type,
                        inm->RPM.token[j].value,
                        inm->RPM.token[j].line);
            } else {
                TOKEN token1 = tokenGETLast(&stack);
                tokenDelLast(&stack);
                TOKEN token2 = tokenGETLast(&stack);
                tokenDelLast(&stack);
                int addrsrc;
                int addrdst;
                if (strcmp(token2.value, "STACK") == 0
                    && strcmp(token1.value, "STACK") == 0) {
                    addrsrc = stacksizeDopCells;
                    stacksizeDopCells--;
                    addrdst = stacksizeDopCells;
                } else if (
                        strcmp(token2.value, "STACK") != 0
                        && strcmp(token1.value, "STACK") == 0) {
                    addrsrc = nameTableAddresGet(token2.value);
                    addrdst = stacksizeDopCells;
                } else if (
                        strcmp(token2.value, "STACK") == 0
                        && strcmp(token1.value, "STACK") != 0) {
                    addrdst = stacksizeDopCells;
                    addrsrc = nameTableAddresGet(token1.value);
                } else {
                    addrdst = nameTableAddresGet(token2.value);
                    addrsrc = nameTableAddresGet(token1.value);
                    stacksizeDopCells++;
                }
                fprintf(file, "%02X LOAD %02X\n", commandaddr, addrdst);
                commandaddr++;
                if (strcmp(inm->RPM.token[j].value, "+") == 0) {
                    fprintf(file, "%02X ADD %02X\n", commandaddr, addrsrc);
                } else if (strcmp(inm->RPM.token[j].value, "-") == 0) {
                    fprintf(file, "%02X SUB %02X\n", commandaddr, addrsrc);
                } else if (strcmp(inm->RPM.token[j].value, "*") == 0) {
                    fprintf(file, "%02X MUL %02X\n", commandaddr, addrsrc);
                } else if (strcmp(inm->RPM.token[j].value, "/") == 0) {
                    fprintf(file, "%02X DIVIDE %02X\n", commandaddr, addrsrc);
                }
                commandaddr++;
                addrdst = stacksizeDopCells;
                if (j == inm->RPM.tokenCount - 1) {
                    int storeaddr = nameTableAddresGet(inm->operator);
                    if (storeaddr == -1) {
                        return -1;
                    }
                    fprintf(file, "%02X STORE %02X\n", commandaddr, storeaddr);

                } else {
                    fprintf(file, "%02X STORE %02X\n", commandaddr, addrdst);
                }
                tokenAdd(&stack, 0, "STACK", 0);
                commandaddr++;
            }
        }
    }
    return 0;
}

void initialParam(FILE* file)
{
    for (int i = 0; i != nameTable.namecount; i++) {
        char* endptr;
        int value = strtol(nameTable.names[i].key, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }
        int address = nameTableAddresGet(nameTable.names[i].key);
        int sign;
        int command;
        int opperand;
        sc_commandDecode(value, &sign, &command, &opperand);
        fprintf(file,
                "%02x = %c%02X%02X\n",
                address,
                (sign == 0) ? '+' : '-',
                command,
                opperand);
    }
}