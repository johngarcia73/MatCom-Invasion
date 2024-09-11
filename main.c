#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<ncurses.h>
#include<unistd.h>
#include<termios.h>
#include<stdbool.h>
#include<locale.h>
#include"control.h"
#include"map.h"
#include"menu.h"
#include"enemies.h"
#include"player.h"
#include"shoot.h"
#include"game.h"
#include"key.h"
#include"init.h"
#include"audio.h"

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&shootLock, NULL);

    setlocale(LC_ALL, "");
    initscr();

    cbreak();
    noecho();
    curs_set(0);                //  Hides curser
    keypad(stdscr, TRUE);
    timeout(100);

    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_BLACK); 
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_color(COLOR_YELLOW, 404, 268, 132);
    init_pair(7, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(8, COLOR_CYAN, COLOR_CYAN);
    init_color(COLOR_YELLOW + 1, 1000, 500, 0);
    init_pair(9, COLOR_YELLOW + 1,COLOR_YELLOW + 1);
    #define COLOR_SILVER 9
    init_color(COLOR_SILVER, 600, 600, 600);
    init_pair(10, COLOR_SILVER, COLOR_SILVER);
    #define COLOR_GOLDEN 10
    init_color(COLOR_GOLDEN, 700, 700, 0);
    init_pair(11, COLOR_GOLDEN, COLOR_GOLDEN);
    #define COLOR_VIOLET 11
    init_color(COLOR_VIOLET, 350, 0, 700);
    init_pair(12, COLOR_VIOLET, COLOR_VIOLET);
    #define COLOR_RANDOM 12
    init_color(COLOR_RANDOM, 344, 765, 123);
    init_pair(13, COLOR_RANDOM, COLOR_RANDOM);

    
    pthread_t audioThread;

    pthread_create(&audioThread, NULL, playAudio, NULL);

    while (1)
    {    
        mainMenu();
    }

    pthread_mutex_destroy(&lock);
    endwin();

    return 0;
}
