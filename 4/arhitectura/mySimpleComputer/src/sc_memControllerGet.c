#define _POSIX_C_SOURCE 199309L
#include "cache.h"
#include "console.h"
#include "mem.h"
#include "memoryPingTimer.h"
#include "mySimpleComputer.h"
#include "register.h"
#include <signal.h>
#include <stdio.h>

int sc_memoryControllerGet(int address, int* value)
{
    if (address < 0 || address >= memorySize) {
        return -1;
    }

    int addressOffset = (address / SIZE_PAGES) * SIZE_PAGES;
    sc_cacheLruIncriment();

    // cache hit
    for (int i = 0; i != MAX_PAGES; i++) {
        if (cache[i].offset == addressOffset) {
            *value = cache[i].values[address % 10].var;
            cache[i].age = 0;
            return 1;
        }
    }

    // cache miss
    sc_cacheLineLoad(addressOffset);
    int index = sc_cacheLineIndex(addressOffset);
    *value = cache[index].values[address % 10].var;

    sc_regSet(REGISTER_IGNORE_TACT, 1);
    int ignoreTacts;
    sc_ignoreSet(memoryPing);
    sc_ignorerGet(&ignoreTacts);
    virtual_timer vt;
    init_vtimer(&vt, 1500000000);
    printCounters();
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