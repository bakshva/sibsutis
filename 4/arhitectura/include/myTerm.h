#ifndef TERM_H
#define TERM_H

enum colors {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    PURPLE = 5,
    LIGHTBLUE = 6,
    WHITE = 7
};

int mt_clrscr(void);
int mt_deline(void);
int mt_getscreensize(int* rows, int* cols);
int mt_gotoXY(int x, int y);
int mt_setbgcolor(enum colors color);
int mt_setcursorvisible(int value);
int mt_setdefaultcolor();
int mt_setfgcolor(enum colors color);

#endif