#ifndef MEMORY_PING_TIMER_H
#define MEMORY_PING_TIMER_H

#include <stdbool.h>
#include <time.h>

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

typedef struct {
    struct timespec interval;
    struct timespec next_tick;
} virtual_timer;

// Инициализация виртуального таймера
void init_vtimer(virtual_timer* vt, long interval_ns);

// Проверка, наступил ли следующий такт
bool check_tick(virtual_timer* vt);

#endif