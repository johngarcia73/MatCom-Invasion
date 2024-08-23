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


int main(int argc, char const *argv[])
{
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&shootLock, NULL);

    setlocale(LC_ALL, "");
    initscr();

    cbreak();
    noecho();
    curs_set(0);
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
    
    while (1)
    {    
        mainMenu();
        pthread_mutex_destroy(&lock);
        pthread_mutex_init(&lock, NULL);
    }
    

    pthread_mutex_destroy(&lock);
    endwin();

    return 0;
}
