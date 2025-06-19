#include "memoryPingTimer.h"

void init_vtimer(virtual_timer* vt, long interval_ns)
{
    vt->interval.tv_sec = interval_ns / 1000000000;
    vt->interval.tv_nsec = interval_ns % 1000000000;
    clock_gettime(CLOCK_MONOTONIC, &vt->next_tick);
    vt->next_tick.tv_nsec += vt->interval.tv_nsec;
    vt->next_tick.tv_sec
            += vt->interval.tv_sec + (vt->next_tick.tv_nsec / 1000000000);
    vt->next_tick.tv_nsec %= 1000000000;
}

bool check_tick(virtual_timer* vt)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    if (now.tv_sec > vt->next_tick.tv_sec
        || (now.tv_sec == vt->next_tick.tv_sec
            && now.tv_nsec >= vt->next_tick.tv_nsec)) {
        vt->next_tick.tv_nsec += vt->interval.tv_nsec;
        vt->next_tick.tv_sec
                += vt->interval.tv_sec + (vt->next_tick.tv_nsec / 1000000000);
        vt->next_tick.tv_nsec %= 1000000000;
        return true;
    }
    return false;
}