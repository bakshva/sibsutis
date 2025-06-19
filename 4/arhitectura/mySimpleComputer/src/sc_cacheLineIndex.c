#include "cache.h"

int sc_cacheLineIndex(int offsetLine)
{
    if (offsetLine < 0 || offsetLine > 120 || offsetLine % 10 != 0) {
        return -2;
    }

    for (int i = 0; i != MAX_PAGES; i++) {
        if (cache[i].offset == offsetLine) {
            return i;
        }
    }
    return -1;
}