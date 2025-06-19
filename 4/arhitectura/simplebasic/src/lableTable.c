#include "basic.h"
#include <stdio.h>
#include <string.h>

void lableTableInit()
{
    memset(lableTable.lables, 0, sizeof(lableTable.lables));
    lableTable.lableCount = 0;
    lableTable.capacity = 128;
}

int lableAdd(int lableB, int lableA)
{
    if (lableTable.lableCount + 1 > lableTable.capacity) {
        return -1;
    }
    lableTable.lables[lableTable.lableCount].lableB = lableB;
    lableTable.lables[lableTable.lableCount].lableA = lableA;
    lableTable.lableCount++;
}

void lableTablePrint()
{
    printf("LableTable: ");
    for (int i = 0; i != lableTable.lableCount; i++) {
        printf("[%d %d] ",
               lableTable.lables[i].lableB,
               lableTable.lables[i].lableA);
    }
    printf("\n");
}

int lableTableGetAddress(int lableB)
{
    for (int i = 0; i != lableTable.lableCount; i++) {
        if (lableTable.lables[i].lableB == lableB) {
            return lableTable.lables[i].lableA;
        }
    }
    return -1;
}