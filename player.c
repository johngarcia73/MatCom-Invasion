#include"player.h"

struct ship player;

struct position shipPositions[8];
int playerPositionsNumber = sizeof(shipPositions)/sizeof(shipPositions[0]);


void drawMunition()
{
    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(5));
    mvprintw(anchoMapa + 2, 30, "Munition: %d       ", player.munition);
    attroff(COLOR_PAIR(5));
    refresh();
    pthread_mutex_unlock(&lock);
}

void erasePlayer()
{
    int x = player.x;
    int y = player.y;

    pthread_mutex_lock(&lock);
    attron(COLOR_PAIR(3));
    
    for (int i = 0; i < playerPositionsNumber; i++)
    {
        space[y + shipPositions[i].y][x + shipPositions[i].x].occupiedByPlayer = false;
        mvaddch(y + shipPositions[i].y, x + shipPositions[i].x, ' ');
    }
    attroff(COLOR_PAIR(3));
    refresh();
    pthread_mutex_unlock(&lock);
}


void setPlayer()
{
    for (int i = 0; i < playerPositionsNumber; i++)
    {  
        if(space[player.y + shipPositions[i].y][player.x + shipPositions[i].x].enemyId != -1)
        {
            destroyEnemy(player.x + shipPositions[i].x, player.y + shipPositions[i].y);

            damageLife();
        }
        space[player.y + shipPositions[i].y][player.x + shipPositions[i].x].occupiedByPlayer = true;
    }
}

void movePlayer(int direction)
{
    switch (direction)
    {
    case 0:
        if(player.x - 3 < 1) break;
        player.x += -3;
        setPlayer();
        break;
    case 1:
        if(player.x + 3 > largoMapa - 2) break;
        player.x += 3;
        setPlayer();
        break;
    case 2:
        if(player.y - 3 < 1) break;
        player.y += -3;
        setPlayer();
        break;
    case 3:
        if(player.y + 3 > anchoMapa - 3) break;
        player.y += 3;
        setPlayer();
        break;
    default:
        break;
    }
    
}