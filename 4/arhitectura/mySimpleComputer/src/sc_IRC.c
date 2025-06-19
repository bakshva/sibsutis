#include "console.h"
#include "mySimpleComputer.h"
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>

void IRC(int signum)
{
    printCounters();
    if (signum == SIGALRM) {
        int ignoreCount;
        sc_ignorerGet(&ignoreCount);
        if (ignoreCount > 0) {
            ignoreCount--;
            sc_ignoreSet(ignoreCount);
            return;
        }
        int IgnoreRegister;
        sc_regGet(REGISTER_IGNORE_TACT, &IgnoreRegister);
        if (IgnoreRegister == 1) {
            return;
        }
        fflush(stdout);

        printcache();
        CU();
    } else if (signum == SIGUSR1) {
        sc_accumulatorInit();
        sc_icounterInit();
        sc_ignoreInit();
    }
}

void TactsGenOn()
{
    signal(SIGALRM, IRC);
    struct itimerval nval;
    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 500;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &nval, NULL);
}

void TactsGenOff()
{
    struct itimerval stop_timer = {
            .it_interval
            = {.tv_sec = 0, .tv_usec = 0}, // интервал = 0 (без повтора)
            .it_value
            = {.tv_sec = 0,
               .tv_usec = 0} // время до срабатывания = 0 (отключить)
    };
    setitimer(ITIMER_REAL, &stop_timer, NULL);
}

int GenChecker()
{
    struct itimerval current_val;
    getitimer(ITIMER_REAL, &current_val);

    if (current_val.it_value.tv_sec == 0 && current_val.it_value.tv_usec == 0) {
        return 0;

    } else {
        return 1;
    }
}