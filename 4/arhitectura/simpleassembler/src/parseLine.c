#include "assembler.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void spacePasser(char* ptr)
{
    while (isspace(*ptr)) {
        ptr++;
    }
}

int parseLine(char* line, Instruction* instr)
{
    if (strstr(line, ";")) {
        *strstr(line, ";") = '\0';
    }

    char* ptr = line;
    spacePasser(ptr);

    if (isxdigit(ptr[0]) && isxdigit(ptr[1]) && isspace(ptr[2])) {
        instr->address = strtol(ptr, NULL, 16);
        ptr += 2;
    } else {
        return -1;
    }
    spacePasser(ptr);
    if (sscanf(ptr, "%9s", instr->command) != 1) {
        return -1;
    }
    ptr += strlen(instr->command) + 1;
    spacePasser(ptr);

    if (sscanf(ptr, "%9s", instr->arg) != 1) {
        return -1;
    }
    return 0;
}