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
    char * mapTile;
    struct enemy * occupierEnemy;
    int enemyId;
    bool occupiedByPlayer;
};



struct position
{
    int x;
    int y;
};

struct tile space[anchoMapa][largoMapa];
char map[anchoMapa][largoMapa];
int positionCounter = 0;

void init();   //Initializes the map with start positions.
void draw();   //Draws the map and its elements.
int* positionGen(int number);       //Generates 'number' random positions.
void keyListener();        //Calls Draw function and identifies if user pressed -> or <-, and updates the ship position.

void cleanPosition(int x, int y);
