#include<time.h>
#include<pthread.h>
#include<ncurses.h>
#include<stdbool.h>
#include"map.h"
#include"menu.h"
#include"control.h"

#pragma once

struct enemy
{
    int coreX;
    int coreY;
    int isAlive;
    int index;
    int level;
    bool abilityUsed;
};

#define left 0
#define right 1
#define up 2
#define down 3
#define maxEnemiesNumber 15

extern struct enemy enemies[10];
extern int numberOfEnemies;
extern struct position enemyPosLv1[16];                                            // Positions around the core that occupies a level 1 enemy.
extern int enemyPositionsNumber;
extern int numberEnemiesSpawned;
extern int numberEnemiesDefeated;
extern int defeatedEnemiesPerPos[8];                // Number of enemies defeated from each spawn position
extern int cap;        // Number of current level spawn positions


extern bool aliveEnemies[8];

extern struct position positionsToSpawnLV1[2];
extern struct position positionsToSpawnLV2[4];
extern struct position positionsToSpawnLV3[6];
extern struct position positionsToSpawnLV4[8];

extern struct position spawnPositions[4];
extern int spwansNumber;
extern int levelSpawnsNumber;

extern int last;           // Position reference of the last generated enemy.

void* spawnEnemy(void* thr);      //Spawn an enemy at coordinates of nextPosition
void driveEnemy(struct enemy e);      //Manages an enemy movement
void setEnemy(struct enemy e);        //Sets an enemy
void cleanEnemy(struct enemy e);      //Disappears an enemy whitout destroying it
void initEnemy(int x, int y);       //Initializes an enemy at coordinates 'x' and 'y'
void drawEnemy(struct enemy e);
void enemiesInit();
void* enemiesManagment(void* thr);
void destroyEnemy(int x, int y);        //Destoyes the enemy at coordinates 'x' and 'y'.
void generateEnemy(int index);
int isOccupiedByEnemy(int x, int y);
bool canPutEnemy(int x, int y);
void moveEnemy(int enemyId, int direction);
void assignenemyPos();
void assignSpawnPos();
void enemyLv2Ability(struct enemy e);
void teleportEnemy(int index, int x, int y);
