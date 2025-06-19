#ifndef MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_H

#include "register.h"

int sc_memoryInit(void);
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);

int sc_regInit(void);
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int* value);

int sc_icounterInit(void);
int sc_icounerSet(int value);
int sc_icounterGet(int* value);

int sc_ignoreInit(void);
int sc_ignoreSet(int value);
int sc_ignorerGet(int* value);

int sc_commandEncode(int sign, int command, int opperand, int* value);
int sc_commandDecode(int value, int* sign, int* command, int* opperand);
int sc_commandValidate(int command);

int sc_accumulatorInit(void);
int sc_accumulatorSet(int value);
int sc_accumulatorGet(int* value);

int ALU(int command, int operand);
void CU(void);
void IRC(int signum);
void TactsGenOn();
void TactsGenOff();
int GenChecker();
int wait_for_ticks(int n);

int sc_memoryControllerSet(int address, int value);
#endif