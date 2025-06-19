#include "myReadKey.h"

int rk_mytermstore(void)
{
    return tcsetattr(1, TCSANOW, &termOptions);
}