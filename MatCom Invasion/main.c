#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<ncurses.h>
#include<unistd.h>
#include<termios.h>
#include<stdbool.h>
#include"control.c"
#include"map.c"
#include"enemies.c"
#include"game.c"
#include"menu.c"
#include"player.c"
#include"shoot.c"
#include"key.c"
#include"init.c"

int main(int argc, char const *argv[])
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);


    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_BLACK); 
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); 

    mainMenu();

    return 0;
}
