#include "assembler.h"

Commands validsCommands[]
        = {{0x00, "NOP"},
           {0x01, "CPUINFO"},
           {0x0A, "READ"},
           {0x0B, "WRITE"},
           {0x14, "LOAD"},
           {0x15, "STORE"},
           {0x1E, "ADD"},
           {0x1F, "SUB"},
           {0x20, "DIVIDE"},
           {0x21, "MUL"},
           {0x28, "JUMP"},
           {0x29, "JNEG"},
           {0x2A, "JZ"},
           {0x2B, "HALT"},
           {0x41, "ADDC"},
           {0x42, "SUBC"},
           {0xFF, "="}};