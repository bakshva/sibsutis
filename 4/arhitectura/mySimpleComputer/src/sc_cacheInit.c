#include "cache.h"
#include "mytype.h"
#include <string.h>

void sc_cacheInit()
{
    for (int i = 0; i != MAX_PAGES; i++) {
        cache[i].age = 0;
        cache[i].offset = -1;
        cache[i].is_dirty = 0;
        memset(cache[i].values, 0, sizeof(cache[i].values));
    }
}