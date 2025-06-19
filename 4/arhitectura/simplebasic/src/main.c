#include "basic.h"
#include <stdio.h>
#include <string.h>

int prevNumberLine = 0;

NAMETABLE nameTable;
LABLETABLE lableTable;

int endpoint = 0;
int currentaddress = 0;

int counCommands = 0;

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
    if (getExtention(argv[1], extention) || strcmp(extention, ".ba")) {
        printf("Неверно заданно расширение файла 1");
        return -3;
    }
    if (getExtention(argv[2], extention) || strcmp(extention, ".sa")) {
        printf("Неверно заданно расширение файла 2");
        return -3;
    }

    nameTableInit();
    lableTableInit();
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", argv[1]);
        return 1;
    }

    char line[256];
    intermediateCode inmCode[128];
    int codeindex = 0;
    while (fgets(line, sizeof(line), file)) {
        TOKENS tokens;
        tokenInit(&tokens);
        if (lexer(line, &tokens)) {
            fclose(file);
            return 2;
        }
        if (parser(&tokens, &inmCode[codeindex])) {
            fclose(file);
            return 3;
        }
        codeindex++;
    }

    genericNamesAddresses();

    if (currentaddress >= 128) {
        printf("Переполнение памяти\n");
        return 1;
    }

    file = fopen(argv[2], "w");
    nameTablePrint();
    lableTablePrint();
    codeGenerator(file, inmCode);
    fclose(file);
}