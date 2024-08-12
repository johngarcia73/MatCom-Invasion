#include"map.h"

pthread_mutex_t lock;
pthread_mutex_t shootLock;


void cleanPosition(int x, int y)
{
    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(3));
    mvaddch(y, x, ' ');
    attroff(COLOR_PAIR(3));
    refresh();

    pthread_mutex_unlock(&lock);

}
