#include <stdio.h>

int bc_strlen(char* str)
{
    if (str == NULL) {
        return -1;
    }

    int symbolCounter = 0;

    char* pointOnByte = str;

    while (*pointOnByte != '\0') {
        unsigned char byte = *pointOnByte;
        int iterationIndex = 0;

        if (byte >> 7 == 0) {
            iterationIndex = 0;
        } else if (byte >> 5 == 0x6) {
            iterationIndex = 1;
        } else if (byte >> 4 == 0xE) {
            iterationIndex = 2;
        } else if (byte >> 3 == 0x1E) {
            iterationIndex = 3;
        } else {
            return -1;
        }

        for (int i = 0; i != iterationIndex; i++) {
            pointOnByte++;
            byte = *pointOnByte;
            if (byte >> 6 != 0x2) {
                return -2;
            }
        }
        symbolCounter++;
        pointOnByte++;
    }
    return symbolCounter;
}