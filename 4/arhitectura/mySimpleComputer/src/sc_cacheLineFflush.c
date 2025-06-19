#include "cache.h"
#include "console.h"
#include "mem.h"
#include "memoryPingTimer.h"
#include "mySimpleComputer.h"
#include "string.h"

// Возворащает индекс строки кеша которую освободил

int sc_cacheLineFflush(int offsetLine)
{
    if (offsetLine < 0 || offsetLine > 120 || offsetLine % 10 != 0) {
        return -1;
    }

    int cacheLineindex = sc_cacheLineIndex(offsetLine);

    if (cacheLineindex == -1) {
        return -1;
    }

    int cacheLineSize = SIZE_PAGES;
    if (offsetLine == 120) {
        cacheLineSize = 8;
    }
    memcpy(&memory[offsetLine],
           cache[cacheLineindex].values,
           sizeof(cache[cacheLineindex].values[0]) * cacheLineSize);

    cache[cacheLineindex].age = 0;
    cache[cacheLineindex].offset = -1;
    memset(cache[cacheLineindex].values,
           0,
           sizeof(cache[cacheLineindex].values[0]) * cacheLineSize);

    int ingnoreTacts = memoryPing;

    sc_regSet(REGISTER_IGNORE_TACT, 1);
    virtual_timer vt;
    if (cache[cacheLineindex].is_dirty) {
        sc_ignoreSet(ingnoreTacts);
        init_vtimer(&vt, 1500000000);
        while (ingnoreTacts != 0) {
            if (check_tick(&vt)) {
                ingnoreTacts--;
                sc_ignoreSet(ingnoreTacts);
                printCounters();
            }
        }
    }
    cache[cacheLineindex].is_dirty = 0;
    printcache();
    for (int i = offsetLine; i != offsetLine + SIZE_PAGES; i++) {
        printCell(i, WHITE, BLACK);
    }
    sc_regSet(REGISTER_IGNORE_TACT, 0);
    return cacheLineindex;
}