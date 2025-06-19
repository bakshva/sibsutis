#include "myReadKey.h"

int rk_mytermsave(void)
{
    return tcgetattr(1, &termOptions);
}