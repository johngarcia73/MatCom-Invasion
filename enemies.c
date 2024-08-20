#include"enemies.h"

struct enemy enemies[10];

int numberOfEnemies = sizeof(enemies)/sizeof(enemies[0]);
struct position enemyPosLv1[16];                                            
int enemyPositionsNumber = sizeof(enemyPosLv1)/sizeof(enemyPosLv1[0]);
int numberEnemiesSpawned = 0;
int numberEnemiesDefeated = 0;
int cap = 0;       

bool aliveEnemies[8];

struct position positionsToSpawnLV1[2];
struct position positionsToSpawnLV2[4];
struct position positionsToSpawnLV3[6];
struct position positionsToSpawnLV4[8];

struct position spawnPositions[4];
int spwansNumber = sizeof(spawnPositions)/sizeof(spawnPositions[0]);
int levelSpawnsNumber;
int last = -1;     


int isOccupiedByEnemy(int x, int y)     //Generalizable, it is possible to return another value for other objects, i.e. return 2 if it is occupied by player.
{
    if(space[y][x].enemyId == -1) return 0;
    return 1;
}

bool canPutEnemy(int x, int y)
{
    if(x<2 || x>=largoMapa-3) return false;                 
    for (int i = 0; i < enemyPositionsNumber; i++)
    {
        if (isOccupiedByEnemy(x + enemyPosLv1[i].x, y + enemyPosLv1[i].y)) return false;
    }
    return true;      
}

void enemiesInit()
{

    switch (level)
    {
    case 1:
        levelSpawnsNumber = 6;
        break;
    
    case 2:
        levelSpawnsNumber = 12;
        break;

    case 3:
        levelSpawnsNumber = 16;
        break;

    case 4:
        levelSpawnsNumber = 22;
        break;
    default:
        break;
    }

    numberEnemiesSpawned = 0;

    switch (level)
    {
    case 1:
        cap = 2;
        break;
    case 2:
        cap = 3;
        break;
    case 3:
        cap = 4;
        break;
    case 4:
        cap = 4;
        break;
    default:
        break;
    }

    srand(time(NULL));              // Initializes enemies properties.

    assignenemyPos();

    assignSpawnPos();

    for (int i = 0; i < 8; i++)
    {
        aliveEnemies[i] = false;
    }
    

    for (int i = 0; i < cap; i++)
    {
        enemies[i].coreX = 10;
        enemies[i].coreY = 10;
        enemies[i].index = 0;
        enemies[i].isAlive = 0;
    }
    
    for (int i = 0; i < cap; i++)
    {
        generateEnemy(i);
    }

    threadPointer += 1;
    usingThread[threadPointer] = true;
    int auxThreadPointer = threadPointer;

    pthread_create(&threads[threadPointer], NULL, enemiesManagment, NULL);
    //pthread_join(threads[auxThreadPointer], NULL);
}

void generateEnemy(int index)
{
    if(numberEnemiesSpawned >= levelSpawnsNumber) return;

    if(last == cap - 1) last = -1;
    for (int i = last+1; i < cap; i++)
    {
        if(aliveEnemies[i] == false && canPutEnemy(positionsToSpawnLV4[i].x, 1))
        {
            enemies[i].coreX = positionsToSpawnLV4[i].x;
            enemies[i].coreY = 1;
            enemies[i].isAlive = 1;
            enemies[i].index = i;
            aliveEnemies[i] = true;
            setEnemy(enemies[i]);
            drawEnemy(enemies[i]);
            numberEnemiesSpawned++;
            last = i;
            break;
        }
        
        if(i == last) break;
        if(i == cap - 1 && last == -1) break;

        if(i == cap -1) i = -1;
    }
}

void* enemiesManagment(void* thr)           // Manages the enemies movement.
{
    while (1)
    {
        generateEnemy(0);    

        pthread_mutex_lock(&lock);

        for (int j = 0; j < cap; j++)
        {
            if(enemies[j].index == -1 || enemies[j].isAlive == 0) continue;
            moveEnemy(j, down);
            
            drawEnemy(enemies[j]);
            refresh();
        }
        pthread_mutex_unlock(&lock);
        if(restart == true) pthread_exit(NULL);
        napms(1000);
    }
}

void cleanEnemy(struct enemy e)             // Cleans an enemy out of the screen.
{
    int ex = e.coreX;
    int ey = e.coreY;

    //pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(3));
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        mvaddch(ey + enemyPosLv1[i].y, ex + enemyPosLv1[i].x, ' ');
        space[ey + enemyPosLv1[i].y][ex + enemyPosLv1[i].x].enemyId = -1;
    }
    
    attroff(COLOR_PAIR(3));
    //refresh();
    //pthread_mutex_unlock(&lock);
}

void setEnemy(struct enemy e)
{
    int x = e.coreX;
    int y = e.coreY;

    
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        if(space[y + enemyPosLv1[i].y][x + enemyPosLv1[i].x].occupiedByPlayer)
        {
            space[y + enemyPosLv1[i].y][x + enemyPosLv1[i].x].enemyId = e.index;
            pthread_mutex_unlock(&lock);
            destroyEnemy(x + enemyPosLv1[i].x, y + enemyPosLv1[i].y);
            drawPlayer();
            damageLife();
            pthread_mutex_lock(&lock);
            return;
        } 
    }

    for (int i = 0; i < enemyPositionsNumber; i++)
    {
        space[y + enemyPosLv1[i].y][x + enemyPosLv1[i].x].enemyId = e.index;
    }

}

void moveEnemy(int enemyId, int direction)
{
    cleanEnemy(enemies[enemyId]);
    int x = enemies[enemyId].coreX;
    int y = enemies[enemyId].coreY;


    switch (direction)
    {
    case 0:
        if(x - 3 < 2 || !canPutEnemy(x - 3, y)) break;
        enemies[enemyId].coreX += -3;
        setEnemy(enemies[enemyId]);
        break;
    case 1:
        if(x + 3 > largoMapa - 3 || !canPutEnemy(x + 3, y)) break;
        enemies[enemyId].coreX += 3;
        setEnemy(enemies[enemyId]);
        break;
    case 2:
        if(y - 3 < 1 || !canPutEnemy(x, y - 3)) break;
        enemies[enemyId].coreY += -3;
        setEnemy(enemies[enemyId]);
        break;
    case 3:
        if(y + 3 > anchoMapa - 2) restart = true;
        if(!canPutEnemy(x, y + 3)) break;
        enemies[enemyId].coreY += 3;
        setEnemy(enemies[enemyId]);
        break;
    default:
        break;
    }
}

void drawEnemy(struct enemy e)
{
    //pthread_mutex_lock(&lock);

    if(e.isAlive == 0) return;
    
    attron(COLOR_PAIR(4));
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        if(i == 6 || i == 7)
        {
            attron(COLOR_PAIR(1));
            mvaddch(e.coreY + enemyPosLv1[i].y, e.coreX + enemyPosLv1[i].x, ' ');
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(4));
            continue;
        }    
        mvaddch(e.coreY + enemyPosLv1[i].y, e.coreX + enemyPosLv1[i].x, ' ');
    }
    attroff(COLOR_PAIR(4));
    
    //refresh();
    //pthread_mutex_unlock(&lock);
}

void destroyEnemy(int x, int y)                     // Cleans an enemy and set it dead, frees its position from the enemies array.
{
    //if(space[y][x].occupierEnemy == NULL) return;

    //struct enemy * e = space[y][x].occupierEnemy;
    //int coreX = e->coreX;
    //int coreY = e->coreY;
    
    int index = space[y][x].enemyId;
    struct enemy e = enemies[index];
    int coreX = e.coreX;
    int coreY = e.coreY;

    aliveEnemies[index] = false;

    pthread_mutex_lock(&lock);
    
    attron(COLOR_PAIR(3));
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        mvaddch(coreY + enemyPosLv1[i].y, coreX + enemyPosLv1[i].x, ' ');
        space[coreY + enemyPosLv1[i].y][coreX + enemyPosLv1[i].x].enemyId = -1;
    }

    attroff(COLOR_PAIR(3));
    refresh();
    pthread_mutex_unlock(&lock);

    enemies[index].isAlive = 0;

    numberEnemiesDefeated ++;

    if(numberEnemiesDefeated >= levelSpawnsNumber)      // Change of Level
    {
        level++;
        nextLevel = true;
        restart = true;
    }     

}

void assignenemyPos()
{
    enemyPosLv1[0].x = enemyPosLv1[1].y = enemyPosLv1[1].y = enemyPosLv1[2].y = enemyPosLv1[3].y = enemyPosLv1[4].y = enemyPosLv1[5].x = enemyPosLv1[9].x = enemyPosLv1[13].x = 0;
    enemyPosLv1[1].x = enemyPosLv1[6].x = /*enemyPosLv1[8].y =*/ enemyPosLv1[9].y = enemyPosLv1[10].x = /*enemyPosLv1[10].y =*/ enemyPosLv1[11].y = enemyPosLv1[12].y = 1;
    enemyPosLv1[2].x = enemyPosLv1[5].y = enemyPosLv1[6].y = enemyPosLv1[7].x = enemyPosLv1[7].y = enemyPosLv1[8].x = -1;
    enemyPosLv1[3].x = enemyPosLv1[11].x = enemyPosLv1[14].x = /*enemyPosLv1[13].y = enemyPosLv1[14].y = enemyPosLv1[15].y =*/ 2;
    enemyPosLv1[4].x = enemyPosLv1[12].x = enemyPosLv1[15].x = -2;

    enemyPosLv1[8].y = enemyPosLv1[10].y = enemyPosLv1[13].y = enemyPosLv1[14].y = enemyPosLv1[15].y = 0;   //Correction.
    enemyPosLv1[8].x = enemyPosLv1[10].x = enemyPosLv1[13].x = enemyPosLv1[14].x = enemyPosLv1[15].x = 0;
}

void assignSpawnPos()
{
    positionsToSpawnLV1[0].y = positionsToSpawnLV1[1].y = positionsToSpawnLV2[0].y = positionsToSpawnLV2[1].y = positionsToSpawnLV2[2].y = positionsToSpawnLV2[3].y =
    positionsToSpawnLV3[0].y = positionsToSpawnLV3[1].y = positionsToSpawnLV3[2].y = positionsToSpawnLV3[3].y =positionsToSpawnLV3[4].y = positionsToSpawnLV3[5].y =
    positionsToSpawnLV4[0].y = positionsToSpawnLV4[1].y =positionsToSpawnLV4[2].y = positionsToSpawnLV4[3].y =positionsToSpawnLV4[4].y = positionsToSpawnLV4[5].y =
    positionsToSpawnLV4[6].y = positionsToSpawnLV4[7].y = 1; 

    positionsToSpawnLV1[0].x = positionsToSpawnLV2[0].x = positionsToSpawnLV3[0].x = positionsToSpawnLV4[0].x  = 71;
    positionsToSpawnLV1[1].x = positionsToSpawnLV2[1].x = positionsToSpawnLV3[1].x = positionsToSpawnLV4[1].x  = 111;
    positionsToSpawnLV2[2].x = positionsToSpawnLV3[2].x = positionsToSpawnLV4[2].x = 41;
    positionsToSpawnLV2[3].x = positionsToSpawnLV3[3].x = positionsToSpawnLV4[3].x = 141;
    positionsToSpawnLV3[4].x = positionsToSpawnLV4[4].x = 31;
    positionsToSpawnLV3[5].x = positionsToSpawnLV4[5].x = 151;
    positionsToSpawnLV4[6].x = 11;
    positionsToSpawnLV4[7].x = 171;
}

