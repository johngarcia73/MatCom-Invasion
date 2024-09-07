#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<ncurses.h>
#include<unistd.h>
#include<stdbool.h>
#include"control.h"

#pragma once

#define largoMapa 181
#define anchoMapa 41

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

struct ship
{
    int x;
    int y;
    int lifes;
    int munition;
};

extern struct ship player;

extern struct position shipPositions[8];
extern int playerPositionsNumber;


extern const char enemy;

extern pthread_mutex_t lock;
extern pthread_mutex_t shootLock;

extern struct position options[2];
extern int option;
extern int optionsNumber;

extern struct tile space[anchoMapa][largoMapa];
extern char map[anchoMapa][largoMapa];
extern int positionCounter;

extern const int totalLevels; 
extern int level;
extern bool winner;
extern bool nextLevel;

int* positionGen(int number);       //Generates 'number' random positions.
void cleanPosition(int x, int y);
void drawLifes();
void damageLife();
void drawPlayer();
void drawGround();
void drawLevel();