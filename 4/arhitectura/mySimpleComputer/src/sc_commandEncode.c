#include "mytype.h"

int sc_commandEncode(int sign, int command, int opperand, int* value)
{
    command = (unsigned int)command;
    opperand = (unsigned int)opperand;
    if (!(sign == 0 || sign == 1)) {
        return -1;
    }
    if (command < 0 || command > 128) {
        return -1;
    }
    if (opperand < 0 || opperand > 128) {
        return -1;
    }
    int_15bit answer;
    answer.var = 0;
    answer.var = answer.var | sign;
    answer.var = (answer.var << 7) | command;
    answer.var = (answer.var << 7) | opperand;
    *value = answer.var;
    return 0;
}