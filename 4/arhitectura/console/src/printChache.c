#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>

#include "cache.h"

void printcache()
{
    int y = 20;
    for (int i = 0; i != MAX_PAGES; i++) {
        mt_gotoXY(2, y);
        if (cache[i].offset == -1) {
            printf(" -1:                                                       "
                   " "
                   "   \n");
            y++;
            continue;
        }
        printf("%0*d: ", 3, cache[i].offset);

        int elementsInLine;
        if (cache[i].offset == 120) {
            elementsInLine = 8;
        } else {
            elementsInLine = 10;
        }

        fflush(stdout);

        int x = 6;
        for (int j = 0; j != elementsInLine; j++) {
            mt_gotoXY(x, y);
            int sign;
            int opperand;
            int command;
            int value = cache[i].values[j].var;
            sc_commandDecode(
                    cache[i].values[j].var, &sign, &command, &opperand);
            printf("%c%0*X%0*X",
                   (sign == 0) ? '+' : '-',
                   2,
                   command,
                   2,
                   opperand);
            x += 6;
            fflush(stdout);
        }
        fflush(stdout);
        y++;
    }
    fflush(stdout);
}