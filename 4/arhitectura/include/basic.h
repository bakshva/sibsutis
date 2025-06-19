#ifndef BASIC_H
#define BASIC_H

#define MAX_TOKENS_ON_LINE 50
#define MAX_TOKEN_LEN 16

#define MAX_NAME_LEN 16

#include <stdio.h>

extern int counCommands;

typedef struct {
    int line_number;
    char command[10];
    char args[256];
} Line;

typedef struct {
    char key[10];
    int address;
} namesTableNode;

typedef struct {
    namesTableNode names[128];
    int namecount;
} NAMETABLE;

extern int endpoint;

extern NAMETABLE nameTable;
int nameTableAddresGet(char* val);
extern int prevNumberLine;
extern int currentaddress;
extern char validcommands[7][15];

void nameTableInit();
int isName(char* ptr);
int addName(char* name);
void nameTableUpdate();
void nameTablePrint();
int nameTableInitialesated();

typedef enum TOKENTYPE {
    TOKENLINE = 0,
    TOKENCOMMAND = 1,
    TOKENNAME = 2,
    TOKENLABLE = 3,
    TOKENLBRACKET = 4,
    TOKENRBRACKET = 5,
    TOKENOPERATOR = 6
} TOKENTYPE;

typedef struct {
    TOKENTYPE type;
    char value[MAX_TOKEN_LEN];
    int line;
    int pos;
} TOKEN;

typedef struct {
    TOKEN token[MAX_TOKENS_ON_LINE];
    int tokenCount;
    int tokenCapacity;
} TOKENS;

void tokenInit(TOKENS* tokens);
int tokenAdd(TOKENS* tokens, int type, char* value, int line);

int lexer(char* line, TOKENS* tokens);

typedef enum {
    REM = 0,
    INPUT = 1,
    OUTPUT = 2,
    GOTO = 3,
    IF = 4,
    LET = 5,
    END = 6
} CommandType;

typedef struct intermediateCode {
    CommandType typeCmd; // стандартные поля
    int address;

    char operator[MAX_NAME_LEN]; // поле для INPUT OUTPUT
    int operatoraddr;

    int lable; // поля для GOTO
    int lableAddress;

    char loperator[MAX_NAME_LEN];
    char roperator[MAX_NAME_LEN]; // поля для второго оператора (IF)
    char logOperator;
    CommandType typeCmd2;
    int opperator3;
    int opperator3addr;

    TOKENS RPM;

} intermediateCode;

int tokenDelLast(TOKENS* tokens);
TOKEN tokenGETLast(TOKENS* tokens);
int parser(TOKENS* tokens, intermediateCode* InmCode);

typedef struct lableTableNode {
    int lableB;
    int lableA;
} lableTableNode;

typedef struct lableTable {
    lableTableNode lables[128];
    int lableCount;
    int capacity;
} LABLETABLE;

void lableTableInit();
int lableAdd(int lableB, int lableA);
void lableTablePrint();
int lableTableGetAddress(int lableB);
void lableTableUpdateOffsets();
extern LABLETABLE lableTable;

void genericNamesAddresses();

int codeGenerator(FILE* file, intermediateCode* inm);

int RpnCountOperations(TOKENS* RPN);

#endif