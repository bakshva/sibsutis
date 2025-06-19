#ifndef MYREADKEY_H
#define MYREADKEY_H

#include <termios.h>

enum keys {
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_F5,
    KEY_F6,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_PLUS,
    KEY_MINUS,
    KEY_ZERO = 48,
    KEY_ONE = 49,
    KEY_TWO = 50,
    KEY_THREE = 51,
    KEY_FOUR = 52,
    KEY_FIFE = 53,
    KEY_SIX = 54,
    KEY_SEVEN = 55,
    KEY_EIGHT = 56,
    KEY_NINE = 57,
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_i = 105,
    KEY_r = 114,
    KEY_l = 108,
    KEY_s = 115,
    KEY_t = 116,
    KEY_OTHER
};

extern struct termios termOptions;

int rk_mytermsave(void);
int rk_mytermstore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
int rk_readkey(enum keys* key);
int rk_readvalue(int* value);

#endif