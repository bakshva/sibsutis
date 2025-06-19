#include "assembler.h"
#include "mySimpleComputer.h"
#include <stdio.h>
#include <string.h>

int getExtention(char* string, char* buffer)
{
    int n = strlen(string);
    int extpos = -1;
    for (int i = n - 1; i != 0; i--) {
        if (string[i] == '.') {
            if (i == n - 1) {
                break;
            }
            extpos = i;
            break;
        }
    }
    if (extpos == -1) {
        return -1;
    }
    strcpy(buffer, &string[extpos]);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Неверное количество входных файлов");
        return -4;
    }
    char extention[256];
    if (getExtention(argv[1], extention) || strcmp(extention, ".sa")) {
        printf("Неверно заданно расширение файла 1");
        return -3;
    }
    if (getExtention(argv[2], extention) || strcmp(extention, ".o")) {
        printf("Неверно заданно расширение файла 2");
        return -3;
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Ошибка чтения файла");
        return -1;
    }
    char buffer[256];
    sc_memoryInit();
    while (fgets(buffer, sizeof(buffer), file)) {
        Instruction instruct;
        if (parseLine(buffer, &instruct)) {
            printf("При парсинге возникла ошибка синтаксиса");
            return -1;
        }
        if (placeCommand(&instruct)) {
            printf("Возникла ошибка (скорее всего в валидации)");
            return -2;
        }
    }
    sc_memorySave(argv[2]);
    fclose(file);
}