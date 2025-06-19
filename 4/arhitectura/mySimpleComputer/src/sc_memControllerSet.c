#include "cache.h"
#include "console.h"
#include "mem.h"
#include "memoryPingTimer.h"
#include "mySimpleComputer.h"
#include "register.h"
#include <stdbool.h>
#include <time.h>

int sc_memoryControllerSet(int address, int value)
{
    if (address < 0 || address >= memorySize) {
        return -1;
    }
    if (value < -16384 || value > 16383) {
        return -1;
    }

    int addressOffset = (address / SIZE_PAGES) * SIZE_PAGES;
    sc_cacheLruIncriment();

    // cache hit
    for (int i = 0; i != MAX_PAGES; i++) {
        if (cache[i].offset == addressOffset) {
            cache[i].values[address % 10].var = value;
            cache[i].age = 0;
            cache[i].is_dirty = 1;
            return 1;
        }
    }

    // cache miss
    sc_cacheLineLoad(addressOffset);
    int index = sc_cacheLineIndex(addressOffset);
    cache[index].values[address % 10].var = value;
    cache[index].is_dirty = 1;

    sc_regSet(REGISTER_IGNORE_TACT, 1);
    int ignoreTacts = memoryPing;
    sc_ignoreSet(memoryPing);
    virtual_timer vt;
    init_vtimer(&vt, 1500000000);
    while (ignoreTacts != 0) {
        if (check_tick(&vt)) {
            ignoreTacts--;
            sc_ignoreSet(ignoreTacts);
            printCounters();
        }
    }
    sc_regSet(REGISTER_IGNORE_TACT, 0);

    printcache();
    return 10;
}