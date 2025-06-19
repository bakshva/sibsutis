#include "myTerm.h"
#include <mySimpleComputer.h>
#include <stdio.h>

void printFlags(void)
{
    mt_gotoXY(92, 2);

    int ind = 0;
    sc_regGet(REGISTER_OVERFLOW, &ind);
    if (ind == 0) {
        putchar('_');
    } else {
        putchar('P');
    }
    putchar(' ');
    sc_regGet(REGISTER_DIVIZION_ZERO, &ind);
    if (ind == 0) {
        putchar('_');
    } else {
        putchar('0');
    }
    putchar(' ');
    sc_regGet(REGISTER_MEMORY_OUT, &ind);
    if (ind == 0) {
        putchar('_');
    } else {
        putchar('M');
    }
    putchar(' ');
    sc_regGet(REGISTER_IGNORE_TACT, &ind);
    if (ind == 0) {
        putchar('_');
    } else {
        putchar('T');
    }
    putchar(' ');
    sc_regGet(REGISTER_INCORRECT_COMMAND, &ind);
    if (ind == 0) {
        putchar('_');
    } else {
        putchar('E');
    }
    fflush(stdout);
}
