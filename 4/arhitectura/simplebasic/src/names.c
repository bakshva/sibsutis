#include "basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isName(char* ptr)
{
    if (*ptr == '\0' || ptr == NULL) {
        return 0;
    }

    if (strlen(ptr) == 1 && *ptr >= 65 && *ptr <= 90) {
        return 1;
    }
    char* endptr;
    int value = strtol(ptr, &endptr, 10);
    if (!(*endptr != '\0')) {
        return 1;
    }
    return 0;
}

void nameTableInit()
{
    nameTable.namecount = 0;
    memset(nameTable.names, 0, sizeof(nameTable.names));
}

int addName(char* name)
{
    if (!isName(name)) {
        return -1;
    }

    int sizeNameTable = nameTable.namecount;
    for (int i = 0; i != sizeNameTable; i++) {
        if (strcmp(name, nameTable.names[i].key) == 0) {
            return 0;
        }
    }
    strcpy(nameTable.names[sizeNameTable].key, name);
    nameTable.namecount++;
    return 0;
}

void nameTablePrint()
{
    printf("NameTable: ");
    for (int i = 0; i != nameTable.namecount; i++) {
        printf("[%s %d] ", nameTable.names[i].key, nameTable.names[i].address);
    }
    printf("\n");
}

int nameTableAddresGet(char* val)
{
    for (int i = 0; i != nameTable.namecount; i++) {
        if (strcmp(val, nameTable.names[i].key) == 0) {
            return nameTable.names[i].address;
        }
    }
    return -1;
}

int nameTableInitialesated()
{
    int count = 0;
    for (int i = 0; i != nameTable.namecount; i++) {
        char* endptr;
        int value = strtol(nameTable.names[i].key, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }
        count++;
    }
    return count;
}