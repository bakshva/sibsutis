#include "basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RpmGenerate(TOKENS* dstTokens, TOKENS* tokens, int startPos);
int RpnCountOperations(TOKENS* RPN);

int parser(TOKENS* tokens, intermediateCode* inmCode)
{
    counCommands++;
    lableAdd(tokens->token[0].line, currentaddress);
    if (strcmp(tokens->token[1].value, "REM") == 0) {
        return 0;
    } else if (
            strcmp(tokens->token[1].value, "INPUT") == 0
            || strcmp(tokens->token[1].value, "OUTPUT") == 0) {
        if (strcmp(tokens->token[1].value, "INPUT") == 0) {
            inmCode->typeCmd = INPUT;
        } else {
            inmCode->typeCmd = OUTPUT;
        }
        inmCode->address = currentaddress;
        strcpy(inmCode->operator, tokens->token[2].value);
        inmCode->operatoraddr = -1;
        currentaddress++;
        return 0;
    } else if (strcmp(tokens->token[1].value, "GOTO") == 0) {
        inmCode->address = currentaddress;
        inmCode->typeCmd = GOTO;
        inmCode->lable = atoi(tokens->token[2].value);
        inmCode->lableAddress = -1;
        currentaddress++;
        return 0;
    } else if (strcmp(tokens->token[1].value, "LET") == 0) {
        inmCode->address = currentaddress;
        inmCode->typeCmd = LET;
        strcpy(inmCode->operator, tokens->token[2].value);
        inmCode->operatoraddr = -1;
        tokenInit(&(inmCode->RPM));
        RpmGenerate(&(inmCode->RPM), tokens, 4);
        int countOppeartios = RpnCountOperations(&(inmCode->RPM));
        currentaddress += countOppeartios;
        return 0;
    } else if (strcmp(tokens->token[1].value, "END") == 0) {
        inmCode->address = currentaddress;
        inmCode->typeCmd = END;
        currentaddress++;
        return 0;
    } else if (strcmp(tokens->token[1].value, "IF") == 0) {
        inmCode->address = currentaddress;
        inmCode->typeCmd = IF;
        strcpy(inmCode->loperator, tokens->token[2].value);
        strcpy(inmCode->roperator, tokens->token[4].value);
        inmCode->logOperator = *(tokens->token[3].value);
        int countOppeartios = 3;
        if (strcmp(tokens->token[5].value, "INPUT") == 0) {
            inmCode->typeCmd2 = INPUT;
            strcpy(inmCode->operator, tokens->token[6].value);
            countOppeartios += 1;
        } else if (strcmp(tokens->token[5].value, "OUTPUT") == 0) {
            strcpy(inmCode->operator, tokens->token[6].value);
            inmCode->typeCmd2 = OUTPUT;
            countOppeartios += 1;
        } else if (strcmp(tokens->token[5].value, "GOTO") == 0) {
            inmCode->typeCmd2 = GOTO;
            inmCode->lable = atoi(tokens->token[6].value);
            countOppeartios += 1;
        } else if (strcmp(tokens->token[5].value, "LET") == 0) {
            inmCode->typeCmd2 = LET;
            strcpy(inmCode->operator, tokens->token[6].value);
            tokenInit(&(inmCode->RPM));
            RpmGenerate(&(inmCode->RPM), tokens, 8);
            countOppeartios += RpnCountOperations(&(inmCode->RPM));
        }
        if (inmCode->logOperator == '=' || inmCode->logOperator == '<') {
            countOppeartios++;
        }
        currentaddress += countOppeartios;
    }
    return 0;
}

int RpnCountOperations(TOKENS* RPN)
{
    int count = 0;
    for (int i = 0; i != RPN->tokenCount; i++) {
        if (RPN->token[i].type == TOKENOPERATOR) {
            count += 3;
        }
    }
    if (count == 0) {
        return 2;
    }
    return count;
}

void RpmGenerate(TOKENS* dstTokens, TOKENS* tokens, int startPos)
{
    TOKENS stek;
    tokenInit(&stek);
    TOKEN currenttok;
    for (int i = startPos; i != tokens->tokenCount; i++) {
        currenttok = tokens->token[i];
        if (currenttok.type == TOKENNAME) {
            tokenAdd(
                    dstTokens,
                    currenttok.type,
                    currenttok.value,
                    currenttok.line);
        } else if (currenttok.type == TOKENLBRACKET) {
            tokenAdd(&stek, currenttok.type, currenttok.value, currenttok.line);
        } else if (currenttok.type == TOKENRBRACKET) {
            TOKEN temptok;

            while (temptok = tokenGETLast(&stek),
                   temptok.type != TOKENLBRACKET && stek.tokenCount != 0) {
                tokenAdd(dstTokens, temptok.type, temptok.value, temptok.line);
                tokenDelLast(&stek);
            }
            tokenDelLast(&stek);

        } else if (currenttok.type == TOKENOPERATOR) {
            int currentPrior = (strcmp(currenttok.value, "+") == 0
                                || strcmp(currenttok.value, "-") == 0)
                    ? 0
                    : 1;
            while (stek.tokenCount > 0) {
                TOKEN temptok = tokenGETLast(&stek);
                if (temptok.type != TOKENOPERATOR
                    && temptok.type != TOKENLBRACKET) {
                    break;
                }

                if (temptok.type == TOKENLBRACKET) {
                    break;
                }

                int stekPrior;
                if (strcmp(temptok.value, "+") == 0
                    || strcmp(temptok.value, "-") == 0) {
                    stekPrior = 0;
                } else {
                    stekPrior = 1;
                }

                // выталкиваем, если приоритет в стеке >= текущего
                if (currentPrior > stekPrior) {
                    break;
                }

                tokenDelLast(&stek);
                tokenAdd(dstTokens, temptok.type, temptok.value, temptok.line);
            }
            tokenAdd(&stek, currenttok.type, currenttok.value, currenttok.line);
        }
    }
    while (stek.tokenCount != 0) {
        TOKEN stekTok = tokenGETLast(&stek);
        tokenAdd(dstTokens, stekTok.type, stekTok.value, stekTok.line);
        tokenDelLast(&stek);
    }
}