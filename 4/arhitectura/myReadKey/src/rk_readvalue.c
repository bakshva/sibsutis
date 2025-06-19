#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "mytype.h"
#include <stdio.h>
#include <unistd.h>
// я считаю в моей версии timeout не нужен

/*считаю, что функцию можно было бы реализовать намного проще если бы она не
 * проверяла каждый введенный пользователем символ*/

int rk_readvalue(int* value)
{
    int_15bit answer;
    struct termios Save;
    tcgetattr(1, &Save);

    rk_mytermregime(0, 0, 1, 0, 0);
    enum keys key;
    // ввод знака + или -
    while (rk_readkey(&key), key != KEY_MINUS && key != KEY_PLUS) {
        if (key == KEY_ESCAPE) {
            tcsetattr(1, TCSANOW, &Save);
            return 1;
        }
    }
    tcsetattr(1, TCSANOW, &Save);
    write(1, (key == KEY_PLUS) ? "+" : "-", 1);

    answer.var = (key == KEY_PLUS) ? 0 : 1;
    rk_mytermregime(0, 0, 1, 0, 0);

    // ввод команды 4 16-ных знака
    for (int i = 0; i != 4; i++) {
        while (rk_readkey(&key),
               !((key >= KEY_ZERO && key <= KEY_NINE)
                 || (key >= KEY_A && key <= KEY_F))) {
            if (key == KEY_ESCAPE) {
                tcsetattr(1, TCSANOW, &Save);
                return 1;
            }
        }
        int addCommand = 0;
        if (key >= KEY_ZERO && key <= KEY_NINE) {
            addCommand = key - 48;
        } else {
            addCommand = key - 55;
        }
        int step = (i % 2 == 0) ? 3 : 4;
        /*так как первый 3 байта отвечают за первуй часть числа, а следующие 4
         * за вторую, то ограничение на 1-ю цифру до 8*/
        if (i % 2 == 0 && addCommand >= 0x8) {
            i--;
            continue;
        }
        answer.var <<= step;
        answer.var |= addCommand;
        tcsetattr(1, TCSANOW, &Save);
        char c = key;
        write(1, &c, 1);
        rk_mytermregime(0, 0, 1, 0, 0);
    }
    *value = answer.var;
    tcsetattr(1, TCSANOW, &Save);
    return 0;
}