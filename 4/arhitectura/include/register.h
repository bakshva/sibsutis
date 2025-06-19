#ifndef REGISTER_H
#define REGISTER_H

#include "mytype.h"

extern int_15bit accumulator;
extern int_15bit commandCounter;
extern int_15bit commandIgnoreTacktCounter;

extern int flagsRegister;
#define REGISTER_OVERFLOW 1
#define REGISTER_DIVIZION_ZERO 2
#define REGISTER_MEMORY_OUT 4
#define REGISTER_IGNORE_TACT 8
#define REGISTER_INCORRECT_COMMAND 16

#endif