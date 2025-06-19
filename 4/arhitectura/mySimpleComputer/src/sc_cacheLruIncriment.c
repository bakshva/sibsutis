#include "cache.h"

void sc_cacheLruIncriment()
{
    for (int i = 0; i != MAX_PAGES; i++) {
        cache[i].age++;
    }
}