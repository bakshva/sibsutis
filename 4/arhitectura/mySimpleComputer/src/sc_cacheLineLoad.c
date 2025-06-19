#include "cache.h"
#include "mem.h"
#include <string.h>

int sc_cacheLineLoad(int offsetLine)
{
    if (offsetLine < 0 || offsetLine > 120 || offsetLine % 10 != 0) {
        return -2;
    }
    if (sc_cacheLineIndex(offsetLine) >= 0) {
        return -1; // Такой кеш уже есть
    }
    int enryCacheoffset = cache[0].offset;
    int maxAge = cache[0].age;
    int IntVoidPage = -1;
    for (int i = 0; i != MAX_PAGES; i++) {
        if (cache[i].age > maxAge) {
            maxAge = cache[i].age;
            enryCacheoffset = cache[i].offset;
        }
        if (cache[i].offset == -1) {
            IntVoidPage = i;
            break;
        }
    }

    int indexLine;
    if (IntVoidPage != -1) {
        indexLine = IntVoidPage;
    } else {
        indexLine = sc_cacheLineIndex(enryCacheoffset);
        sc_cacheLineFflush(enryCacheoffset);
    }
    int cacheLineSize = SIZE_PAGES;
    if (offsetLine == 120) {
        cacheLineSize = 8;
    }
    memcpy(cache[indexLine].values,
           &memory[offsetLine],
           sizeof(cache[indexLine].values[0]) * cacheLineSize);
    cache[indexLine].age = 0;
    cache[indexLine].offset = offsetLine;
}