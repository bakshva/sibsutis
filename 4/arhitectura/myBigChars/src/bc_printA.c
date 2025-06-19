#include <stdio.h>
#include <unistd.h>

int bc_printA(char* str)
{
    write(1, "\033(0", 3);
    printf("%s", str);
    fflush(stdout);
    write(1, "\033(B", 3);
    return 0;
}