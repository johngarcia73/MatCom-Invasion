#include"player.h"

void drawPlayer()
{
    int x = player.x;
    int y = player.y;

    *space[y][x].mapTile = player.ascii;
    attron(COLOR_PAIR(1));
    mvaddch(y, x, player.ascii);
    mvaddch(y-1, x, player.ascii);
    mvaddch(y, x+1, player.ascii);
    mvaddch(y, x-1, player.ascii);
    mvaddch(y+1, x+1, player.ascii);
    mvaddch(y+1, x-1, player.ascii);
    mvaddch(y, x+2, player.ascii);
    mvaddch(y, x-2, player.ascii);
    refresh();
}

void erasePlayer()
{
    int x = player.x;
    int y = player.y;

    attron(COLOR_PAIR(3));
    *space[y][x].mapTile = ' ';
    mvaddch(y, x, ' ');
    mvaddch(y-1, x, ' ');
    mvaddch(y, x+1, ' ');
    mvaddch(y, x-1, ' ');
    mvaddch(y+1, x+1, ' ');
    mvaddch(y+1, x-1, ' ');
    mvaddch(y, x+2, ' ');
    mvaddch(y, x-2, ' ');
    attroff(COLOR_PAIR(3));
    refresh();
}

void setPlayer(int x,int y)
{
    int ax = player.x;
    int ay = player.y;

    space[ay][ax].occupiedByPlayer, space[ay-1][ax].occupiedByPlayer, space[ay][ax+1].occupiedByPlayer, 
    space[ay][ax-1].occupiedByPlayer, space[ay+1][ax+1].occupiedByPlayer, space[ay+1][ax-1].occupiedByPlayer, 
    space[ay][ax+2].occupiedByPlayer, space[ay][ax-2].occupiedByPlayer = false;
    
    for (int i = 0; i < sizeof(shipPositions)/sizeof(shipPositions[0]); i++)
    {  
        if(space[y + shipPositions[i].y][x + shipPositions[i].x].enemyId != -1)
        {
            destroyEnemy(x + shipPositions[i].x, y + shipPositions[i].y);
            damageLife();
        } 
    }
    

    
    player.x = x;
    player.y = y;
    space[y][x].occupiedByPlayer, space[y-1][x].occupiedByPlayer, space[y][x+1].occupiedByPlayer, 
    space[y][x-1].occupiedByPlayer, space[y+1][x+1].occupiedByPlayer, space[y+1][x-1].occupiedByPlayer, 
    space[y][x+2].occupiedByPlayer, space[y][x-2].occupiedByPlayer = true;
}

void damageLife()
{
    player.lifes --;
    attron(COLOR_PAIR(5));
    mvprintw(anchoMapa + 2, 1, "Lifes: %d", player.lifes);
    attroff(COLOR_PAIR(5));
    refresh();
    if (player.lifes <= 0)
    {
        killAll();   
        mainMenu(); 
        return;
    }
    
}