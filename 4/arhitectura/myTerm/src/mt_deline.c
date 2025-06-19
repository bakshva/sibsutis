#include <stdio.h>
#include <unistd.h>

int mt_deline()
{
    int flag = 0;
    flag = write(1, "\033[M", 3);
    if (flag < 3) {
        return -1;
    }
    return 0;
}