#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cache.h"

int is_execute = 0;

int main(int argc, char* argv[])
{
    if (!isatty(1)) {
        printf("Dont term stdout");
        return 1;
    }
    struct winsize WS;

    if (ioctl(1, TIOCGWINSZ, &WS)) {
        printf("can't get term size");
        return 2;
    }

    int fd;
    if (WS.ws_col < 115 && WS.ws_row < 30) {
        printf("cant open interface on your term");
        return 3;
    }
    if (argc > 2) {
        printf("too many command argument");
        return -1;
    } else if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
    } else {
        fd = open("font.bin", O_RDONLY);
    }
    if (fd == -1) {
        printf("error open file");
        return -1;
    }

    int count;
    if (bc_bigcahrread(fd, bigchar[0], 18, &count)) {
        printf("error: cant read file");
        return -1;
    }

    mt_clrscr();

    sc_memoryInit();
    sc_accumulatorInit();
    sc_regInit();
    sc_icounterInit();
    sc_regInit();
    sc_cacheInit();

    printAccumulator();
    printCounters();
    printCommand();
    printFlags();
    printcache();

    nowRedact = 0;

    for (int i = 0; i != 128; i++) {
        if (i == nowRedact) {
            printCell(i, BLACK, WHITE);
            continue;
        }
        printCell(i, WHITE, BLACK);
    }
    int value;
    sc_memoryGet(nowRedact, &value);
    printDecodedCommand(value);

    bc_box(1, 1, 61, 15, WHITE, BLACK, "Оперативная память", RED, BLACK);
    bc_box(1,
           16,
           61,
           3,
           WHITE,
           BLACK,
           "Редактируемая ячейка (формат)",
           RED,
           WHITE);
    bc_box(62, 1, 23, 3, WHITE, BLACK, "Аккумулятор", RED, BLACK);
    bc_box(85, 1, 23, 3, WHITE, BLACK, "Регист флагов", RED, BLACK);
    bc_box(62, 4, 23, 3, WHITE, BLACK, "Счетчик команд", RED, BLACK);
    bc_box(85, 4, 23, 3, WHITE, BLACK, "Команда", RED, BLACK);
    bc_box(62,
           7,
           46,
           12,
           WHITE,
           BLACK,
           "Редактируемая команда (увеличено)",
           RED,
           WHITE);
    bc_box(66, 19, 11, 7, WHITE, BLACK, "IN-OUT", GREEN, WHITE);
    bc_box(1, 19, 65, 7, WHITE, BLACK, "Кэш процессора", GREEN, WHITE);
    bc_box(77, 19, 31, 7, WHITE, BLACK, "Клавиши", GREEN, WHITE);

    mt_gotoXY(78, 20);
    printf("l - load  s - save  i - reset\n");
    fflush(stdout);
    mt_gotoXY(78, 21);
    printf("r - run  t - step\n");
    fflush(stdout);
    mt_gotoXY(78, 22);
    printf("ESC - выход\n");
    fflush(stdout);
    mt_gotoXY(78, 23);
    printf("F5 - accumulator\n");
    fflush(stdout);
    mt_gotoXY(78, 24);
    printf("F6  - instruction counter\n");
    fflush(stdout);

    printBigCell();

    mt_setcursorvisible(0);

    rk_mytermregime(0, 0, 1, 0, 0);

    enum keys key;
    while (rk_readkey(&key), key != KEY_ESCAPE) {
        rk_mytermregime(0, 0, 1, 0, 0);
        if (key == KEY_OTHER) {
            continue;
        } else if (key == KEY_UP) {
            if (nowRedact < 10) {
                continue;
            }
            printCell(nowRedact, WHITE, BLACK);
            nowRedact -= 10;
        } else if (key == KEY_ENTER) {
            mt_setbgcolor(GREEN);
            mt_setfgcolor(BLACK);
            int y = (nowRedact / 10) + 2;
            int x = (nowRedact % 10) * 6 + 1 + 1;
            mt_gotoXY(x, y);
            write(1, "     ", 5);
            mt_gotoXY(x, y);
            int value;
            if (!rk_readvalue(&value)) {
                while (rk_readkey(&key),
                       key != KEY_ENTER && key != KEY_ESCAPE) {
                }
                if (key == KEY_ENTER) {
                    sc_memorySet(nowRedact, value);

                } else if (key == KEY_ESCAPE) {
                }
            }
            mt_setdefaultcolor();
        } else if (key == KEY_F5) {
            mt_setbgcolor(GREEN);
            mt_setfgcolor(BLACK);
            mt_gotoXY(68, 2);
            write(1, "     ", 5);
            mt_gotoXY(68, 2);
            int value;
            if (!rk_readvalue(&value)) {
                while (rk_readkey(&key),
                       key != KEY_ENTER && key != KEY_ESCAPE) {
                }
                if (key == KEY_ENTER) {
                    sc_accumulatorSet(value);

                } else if (key == KEY_ESCAPE) {
                }
            }
            mt_setdefaultcolor();
            printAccumulator();
        } else if (key == KEY_F6) {
            mt_setbgcolor(GREEN);
            mt_setfgcolor(BLACK);
            mt_gotoXY(77, 5);
            write(1, "     ", 5);
            mt_gotoXY(77, 5);

            int value;
            rk_readvalue(&value);
            sc_icounerSet(value);
            mt_setdefaultcolor();
            printCounters();
            printCommand();
        } else if (key == KEY_s) {
            rk_mytermregime(1, 0, 0, 0, 1);
            mt_gotoXY(1, 26);
            mt_deline();
            char buffer[150];
            printf("Введите имя файла для сохораниния: ");
            mt_setcursorvisible(1);
            fgets(buffer, sizeof(buffer), stdin);
            mt_setcursorvisible(0);
            mt_gotoXY(1, 26);
            mt_deline();
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
            if (sc_memorySave(buffer)) {
                printf("Ошибка при сохранении файла %s", buffer);
            } else {
                printf("Файл %s успешно сохранен", buffer);
            }
            fflush(stdout);
            rk_mytermregime(0, 0, 1, 0, 0);
        } else if (key == KEY_l) {
            rk_mytermregime(1, 0, 0, 0, 1);
            mt_gotoXY(1, 26);
            mt_deline();
            char buffer[150];
            printf("Введите имя файла для загрузки: ");
            mt_setcursorvisible(1);
            fgets(buffer, sizeof(buffer), stdin);
            mt_setcursorvisible(0);
            mt_gotoXY(1, 26);
            mt_deline();
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
            if (sc_memoryLoad(buffer)) {
                printf("Ошибка при чтении файла %s", buffer);
            } else {
                mt_gotoXY(1, 26);
                mt_deline();
                printf("Файл %s успешно считан", buffer);
                fflush(stdout);
                sc_accumulatorInit();
                sc_icounterInit();
                printAccumulator();
                printCounters();
                fflush(stdout);
                for (int i = 0; i != 128; i++) {
                    printCell(i, WHITE, BLACK);
                }
            }
            fflush(stdout);
            rk_mytermregime(0, 0, 1, 0, 0);
        } else if (key == KEY_i) {
            sc_memoryInit();
            sc_accumulatorInit();
            sc_regInit();
            sc_icounterInit();
            sc_regInit();
            for (int address = 0; address != 128; address++) {
                printCell(address, WHITE, BLACK);
            }
            printAccumulator();
            printCounters();
            printCommand();
            printFlags();

        } else if (key == KEY_DOWN) {
            if (nowRedact > 117) {
                continue;
            }
            printCell(nowRedact, WHITE, BLACK);
            nowRedact += 10;
        } else if (key == KEY_RIGHT) {
            if (nowRedact == 127) {
                continue;
            }
            printCell(nowRedact, WHITE, BLACK);
            nowRedact++;
        } else if (key == KEY_LEFT) {
            if (nowRedact == 0) {
                continue;
            }
            printCell(nowRedact, WHITE, BLACK);
            nowRedact--;
        } else if (key == KEY_r) {
            is_execute = 1;
            printCell(nowRedact, WHITE, BLACK);
            sc_regSet(REGISTER_IGNORE_TACT, 0);
            TactsGenOn();
            while (is_execute == 1) {
            }
            TactsGenOff();
        } else if (key == KEY_t) {
            CU();
            printAccumulator();
            printCounters();
        }

        printCell(nowRedact, BLACK, WHITE);
        printBigCell();
        printFlags();
        printAccumulator();
        printCounters();
        printCommand();
        printcache();
        int value;
        sc_memoryGet(nowRedact, &value);
        printDecodedCommand(value);
        mt_gotoXY(1, 30);
    }
    mt_gotoXY(1, 26);
    mt_setcursorvisible(1);
    rk_mytermregime(1, 0, 0, 0, 0);
    return 0;
}