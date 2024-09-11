#include<time.h>
#include<pthread.h>
#include<ncurses.h>
#include<stdbool.h>
#include"map.h"
#include"menu.h"
#include"control.h"
#include"shoot.h"

#pragma once

typedef struct
{
    int coreX;
    int coreY;
    int isAlive;
    int index;
    int level;
    bool abilityUsed;
    int zone;
    int shotCooldown;
    int movementDirection;
    struct position *positionsArray;
    int positionsNumber;
} enemy;

#define left 0
#define right 1
#define up 2
#define down 3
#define maxEnemiesNumber 15
#define zonesNumber 3

extern enemy enemies[20];
extern int numberOfEnemies;
extern struct position enemyPosLv1[11];                                            // Positions around the core that occupies a level 1 or 2 enemy.
extern struct position enemyPosLv3[9];                                            // Positions around the core that occupies a level 3 enemy.
extern struct position enemyPosBoss[83];                                            // Positions around the core that occupies the final boss.

extern int enemyPositionsNumber;
extern int numberEnemiesSpawned;
extern int numberEnemiesDefeated;
extern int defeatedEnemiesPerZone[zonesNumber];                // Number of enemies defeated from each zone
extern int cap;        // Number of current level spawn positions


extern bool aliveEnemies[8];

extern struct position positionsToSpawnLV1[2];
extern struct position positionsToSpawnLV2[4];
extern struct position positionsToSpawnLV3[6];
extern struct position positionsToSpawnLV4[8];

extern struct position spawnPositions[4];
extern int spwansNumber;
extern int levelSpawnsNumber;

extern int bossLife;

extern int last;           // Position reference of the last generated enemy.

void* spawnEnemy(void* thr);      //Spawn an enemy at coordinates of nextPosition
void driveEnemy(enemy e);      //Manages an enemy movement
void setEnemy(enemy e);        //Sets an enemy
void cleanEnemy(enemy e);      //Disappears an enemy whitout destroying it
void initEnemy(int x, int y);       //Initializes an enemy at coordinates 'x' and 'y'
void drawEnemy(enemy e);
void enemiesInit();
void* enemiesManagment(void* thr);
void destroyEnemy(int x, int y);        //Destoyes the enemy at coordinates 'x' and 'y'.
void generateEnemy(int index);
int isOccupiedByEnemy(int x, int y);
bool canPutEnemy(int x, int y, int level);
void moveEnemy(int enemyId, int direction);
void moveBoss(enemy e);
void assignenemyPos();
void assignSpawnPos();
void enemyLv2Ability(enemy e);
void enemyLv3Ability(enemy e);
void teleportEnemy(int index, int x, int y);
void enemyShoot(enemy e);
int genRandTeleportPosition(int leftBorder, int rightBorder, enemy e);
void generate(enemy e, int index);
void damageBossLife();