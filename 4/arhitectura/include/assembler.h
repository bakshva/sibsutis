#ifndef ASSEMBLER_H
#define ASSEMBLER_H

typedef struct {
    int command;
    char* commandName;
} Commands;

extern Commands validsCommands[17];

typedef struct {
    int address;
    char command[10];
    char arg[10];
    int commandVal; // значение команды в численной форме
    int argVal; // значение аргумента в численной форме
} Instruction;

int parseLine(char* line, Instruction* instr);
void spacePasser(char* ptr);
int Validate(Instruction inst);
int placeCommand(Instruction* inst);

#endif