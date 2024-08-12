#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<ncurses.h>
#include<unistd.h>
#include<stdbool.h>

#define largoMapa 181
#define anchoMapa 41
const char enemy = (char)208;


struct tile
{
    int posX;
    int posY;
    int enemyId;
    bool occupiedByPlayer;
};


struct position
{
    int x;
    int y;
};

struct position options[2];
int option = 0;
int optionsNumber = sizeof(options)/sizeof(options[0]);

struct tile space[anchoMapa][largoMapa];
char map[anchoMapa][largoMapa];
int positionCounter = 0;


int* positionGen(int number);       //Generates 'number' random positions.
void cleanPosition(int x, int y);
