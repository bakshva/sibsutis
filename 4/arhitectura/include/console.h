#ifndef CONSOLE_H
#define CONSOLE_H

#include "myTerm.h"
void printAccumulator(void);
void printCell(int address, enum colors fg, enum colors bg);
void printCounters(void);
void printDecodedCommand(int value);
void printFlags(void);
int printTerm(int address, int input);
void printCommand(void);
void printBigCell(void);
void printcache(void);

extern int nowRedact;

#endif