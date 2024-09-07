#include"map.h"

const char enemy = (char)208;

pthread_mutex_t lock;
pthread_mutex_t shootLock;

struct position options[2];
int option = 0;
int optionsNumber = sizeof(options)/sizeof(options[0]);

struct tile space[anchoMapa][largoMapa];
char map[anchoMapa][largoMapa];
int positionCounter = 0;

const int totalLevels = 4; 
int level = 1;
bool nextLevel= false;
bool winner = false;

void drawPlayer()
{
    int x = player.x;
    int y = player.y;

    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(1));

    for (int i = 0; i < playerPositionsNumber; i++)
    {
        mvaddch(y + shipPositions[i].y, x + shipPositions[i].x, ' ');
    }
    attroff(COLOR_PAIR(1));
    
    refresh();

    pthread_mutex_unlock(&lock);

}

void cleanPosition(int x, int y)
{
    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(3));
    mvaddch(y, x, ' ');
    attroff(COLOR_PAIR(3));
    refresh();

    pthread_mutex_unlock(&lock);

}

void drawLifes()
{
    pthread_mutex_lock(&lock);
    attron(COLOR_PAIR(5));
    mvprintw(anchoMapa + 2, 1, "Lifes: %d", player.lifes);
    attroff(COLOR_PAIR(5));
    refresh();
    pthread_mutex_unlock(&lock);
}

void damageLife()
{
    player.lifes --;

    drawLifes();

    if(player.lifes <= 0) restart = true;
}

void drawGround()
{
    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(7));
    for (int i = 0; i < largoMapa + 3; i++)
    {
        for (int j = anchoMapa+1; j > anchoMapa - 2; j--)
        {
            mvaddch(j, i, ' ');
        }
    }
    
    attroff(COLOR_PAIR(7));
    refresh();
    
    pthread_mutex_unlock(&lock);
}

void drawLevel()
{
    pthread_mutex_lock(&lock);
    attron(COLOR_PAIR(5));
    mvprintw(anchoMapa + 2, 61, "Level: %d", level);
    attroff(COLOR_PAIR(5));
    refresh();
    pthread_mutex_unlock(&lock);
}