#include "basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inputOutputLex(char* token, int numberLine, TOKENS* tokens);
int goToLex(char* token, int numberLine, TOKENS* tokens);
int ifLex(char* token, int numberLine, TOKENS* tokens);
int letLex(char* token, int numberLine, TOKENS* tokens);

int lexer(char* line, TOKENS* tokens)
{
    char* token = strtok(line, " ");
    char* endptr;
    int numberLine = strtol(token, &endptr, 10);
    if (*endptr != '\0' || numberLine % 10 != 0
        || numberLine < prevNumberLine) {
        printf("Ошибка в номере строки -> %s\n", token);
        return -1;
    }

    if (tokenAdd(tokens, TOKENLINE, token, numberLine)) {
        return -1;
    }

    prevNumberLine = numberLine;
    token = strtok(NULL, " \n");

    int flag = 0;

    for (int i = 0; i != sizeof(validcommands) / sizeof(validcommands[0]);
         i++) {
        if (strcmp(token, validcommands[i]) == 0) {
            flag = 1;
        }
    }

    if (flag == 0) {
        printf("В строке %d невверна введена команда -> %s\n",
               numberLine,
               token);
        return -1;
    }

    if (tokenAdd(tokens, TOKENCOMMAND, token, numberLine)) {
        return -1;
    }

    if (!strcmp(token, "REM")) {
        return 0;
    } else if (!strcmp(token, "INPUT") || !strcmp(token, "OUTPUT")) {
        if (inputOutputLex(token, numberLine, tokens)) {
            return -1;
        }
    } else if (!strcmp(token, "GOTO")) {
        if (goToLex(token, numberLine, tokens)) {
            return -1;
        }
    } else if (!strcmp(token, "IF")) {
        if (ifLex(token, numberLine, tokens)) {
            return -1;
        }
    } else if (!strcmp(token, "LET")) {
        if (letLex(token, numberLine, tokens)) {
            return -1;
        }

    } else if (!strcmp(token, "END")) {
        if (endpoint > 0) {
            printf("В программе может быть только одна точка выхода!\n");
            return -1;
        }
        endpoint = 1;
        return 0;
    }
}

int inputOutputLex(char* token, int numberLine, TOKENS* tokens)
{
    token = strtok(NULL, " \n");
    if (strlen(token) == 1 && *token >= 'A' && *token <= 'Z') {
        addName(token);
        tokenAdd(tokens, TOKENNAME, token, numberLine);
        token = strtok(NULL, " ");
        if (token == NULL) {
            return 0;
        }
    }
    printf("Ошибка: Неправильное имя в строке %d\n", numberLine);
    return -1;
}

int goToLex(char* token, int numberLine, TOKENS* tokens)
{
    token = strtok(NULL, " \n");
    char* endptr;
    int NumberGoToLine = strtol(token, &endptr, 10);
    if (*endptr != '\0' || NumberGoToLine % 10 != 0) {
        printf("Ошибка: Неправильно указана метка в строке %d", numberLine);
        return -1;
    }
    tokenAdd(tokens, TOKENLABLE, token, numberLine);
    token = strtok(NULL, " ");
    if (token == NULL) {
        return 0;
    }
    return -1;
}

int ifLex(char* token, int numberLine, TOKENS* tokens)
{
    token = strtok(NULL, " \n");

    if (!isName(token)) {
        return -1;
    }
    addName(token);
    tokenAdd(tokens, TOKENNAME, token, numberLine);

    token = strtok(NULL, " ");

    if (!(*token == '>' || *token == '<' || *token == '=')) {
        return -1;
    }
    tokenAdd(tokens, TOKENOPERATOR, token, numberLine);

    token = strtok(NULL, " ");

    if (!isName(token)) {
        return -1;
    }
    addName(token);
    tokenAdd(tokens, TOKENNAME, token, numberLine);

    token = strtok(NULL, " ");

    int flag = 0;
    for (int i = 0; i != sizeof(validcommands); i++) {
        if (strcmp(token, validcommands[i]) == 0) {
            flag = 1;
        }
    }

    if (flag == 0 || strcmp(token, "IF") == 0 || strcmp(token, "END") == 0
        || strcmp(token, "REM") == 0) {
        printf("В строке %d невверна введена команда -> %s\n",
               numberLine,
               token);
        return -1;
    }
    tokenAdd(tokens, TOKENCOMMAND, token, numberLine);
    if (strcmp(token, "INPUT") == 0 || strcmp(token, "OUTPUT") == 0) {
        if (inputOutputLex(token, numberLine, tokens)) {
            return -1;
        }
        return 0;
    } else if (strcmp(token, "GOTO") == 0) {
        if (goToLex(token, numberLine, tokens)) {
            return -1;
        }
        return 0;
    } else if (strcmp(token, "LET") == 0) {
        if (letLex(token, numberLine, tokens)) {
            return -1;
        }
        return 0;
    }

    return -1;
}

int letLex(char* token, int numberLine, TOKENS* tokens)
{
    token = strtok(NULL, " \n");
    if (!((*token >= 'A' && *token <= 'Z') && strlen(token) == 1)) {
        printf("Ошибка: в строке %d неправильная переменная %s",
               numberLine,
               token);
        return -1;
    }
    addName(token);
    tokenAdd(tokens, TOKENNAME, token, numberLine);
    token = strtok(NULL, " ");
    if (strcmp(token, "=")) {
        printf("ожидается знак = в строке %d", numberLine);
    }
    tokenAdd(tokens, TOKENOPERATOR, token, numberLine);

    token = strtok(NULL, " \n");

    int is_operator = 0;
    int UnClosedBraced = 0;
    int values = 0;
    char operators[4][2] = {"+", "-", "*", "/"};
    do {
        if (is_operator) {
            for (int i = 0; i != 4; i++) {
                if (strcmp(token, operators[i]) == 0) {
                    tokenAdd(tokens, TOKENOPERATOR, token, numberLine);
                    is_operator = 0;
                }
            }
            if (is_operator) {
                if (strcmp(token, ")") == 0) {
                    tokenAdd(tokens, TOKENRBRACKET, token, numberLine);
                    UnClosedBraced--;
                } else {
                    printf("Неккоректное выражение в строке %d", numberLine);
                    return -1;
                }
            }
        } else {
            if (isName(token)) {
                addName(token);
                tokenAdd(tokens, TOKENNAME, token, numberLine);
                values++;
                is_operator = 1;
            }
            if (is_operator == 0) {
                if (strcmp(token, "(") == 0) {
                    tokenAdd(tokens, TOKENLBRACKET, token, numberLine);
                    UnClosedBraced++;
                } else {
                    printf("Неккоректное выражение в строке %d %s",
                           numberLine,
                           token);
                    return -1;
                }
            }
        }
        if (UnClosedBraced < 0) {
            printf("Ошибка: непарный ) в строке %d", numberLine);
            return -1;
        }
        token = strtok(NULL, " \n");
    } while (token != NULL);

    if (UnClosedBraced > 0) {
        printf("Не парное ( в строке %d", numberLine);
        return -1;
    }
    if (is_operator == 0) {
        printf("Лишний знак в выражение в строке %d", numberLine);
        return -1;
    }

    if (values > 0 && UnClosedBraced == 0) {
        return 0;
    }
    return -1;
}