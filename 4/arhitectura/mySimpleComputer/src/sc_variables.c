#include "mem.h"
#include "register.h"

int_15bit memory[memorySize];

int_15bit accumulator;
int_15bit commandCounter;
int flagsRegister;
int_15bit commandIgnoreTacktCounter;