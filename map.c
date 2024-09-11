#include<stdio.h>
#include<string.h>
#include"map.h"

const char enem = (char)208;

pthread_mutex_t lock;
pthread_mutex_t shootLock;

struct position options[2];
int option = 0;
int optionsNumber = sizeof(options)/sizeof(options[0]);

struct tile space[anchoMapa][largoMapa];
char map[anchoMapa][largoMapa];
int positionCounter = 0;

const int totalLevels = 5; 
int level = 1;
bool nextLevel= false;
bool winner = false;

void drawPlayer()
{
    int x = player.x;
    int y = player.y;

    for (int i = 0; i < playerPositionsNumber; i++)
    {
        draw(x + shipPositions[i].x, y + shipPositions[i].y, " ", 1);
    }

}

void cleanPosition(int x, int y)
{
    draw(x, y, " ", 3);
}

void drawLifes()
{
    char str[10] = "Lifes: ";
    char numStr[10];
    sprintf(numStr, "%d", player.lifes);
    strcat(str, numStr);
    draw(1, anchoMapa + 2, str, 5);
}

void damageLife()
{
    if(player.lifes > 0)player.lifes --;

    drawLifes();

    if(player.lifes <= 0) restart = true;
}

void drawGround()
{
    for (int i = 0; i < largoMapa + 3; i++)
    {
        for (int j = anchoMapa+1; j > anchoMapa - 2; j--)
        {
            draw(i, j, " ", 7);
        }
    }
    
}

void drawLevel()
{
    char str[10] = "Level: ";
    char numStr[10];
    sprintf(numStr, "%d", level);
    strcat(str, numStr);
    draw(61, anchoMapa + 2, str, 5);
}

void draw(int x, int y, char *string, int colorPair)
{
    pthread_mutex_lock(&lock);
    attron(COLOR_PAIR(colorPair));
    mvprintw(y, x, "%s", string);
    attroff(COLOR_PAIR(colorPair));
    refresh();
    pthread_mutex_unlock(&lock);
}