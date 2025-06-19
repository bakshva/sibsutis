#include "myReadKey.h"
/*
regime = 1 - канон
regime = 0 - не канон
*/
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios options;

    if (tcgetattr(0, &options) != 0)
        return -1;

    if (regime == 0) {
        options.c_lflag &= ~(ICANON);
        if (echo == 0) {
            options.c_lflag &= ~(ECHO);
        } else {
            options.c_lflag |= ECHO;
        }
        if (sigint == 0) {
            options.c_lflag &= ~(ISIG);
        } else {
            options.c_lflag |= ISIG;
        }
        options.c_cc[VMIN] = vmin;
        options.c_cc[VTIME] = vtime;
    } else {
        options.c_lflag |= ICANON;
        options.c_lflag |= ECHO;
        options.c_lflag |= ISIG;
    }
    return tcsetattr(0, TCSANOW, &options);
}