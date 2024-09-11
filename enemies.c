#include"enemies.h"

enemy enemies[20];

int numberOfEnemies = sizeof(enemies)/sizeof(enemies[0]);
struct position enemyPosLv1[11];     
struct position enemyPosLv3[9];  
struct position enemyPosBoss[83];                                            // Positions around the core that occupies the final boss.

int enemyPositionsNumber = sizeof(enemyPosLv1)/sizeof(enemyPosLv1[0]);
int numberEnemiesSpawned = 0;
int numberEnemiesDefeated = 0;
int cap = 0;       

int defeatedEnemiesPerZone[3];   
bool aliveEnemies[8];

struct position positionsToSpawnLV4[8];

struct position spawnPositions[4];
int spwansNumber = sizeof(spawnPositions)/sizeof(spawnPositions[0]);
int levelSpawnsNumber;
int last = -1;

int bossLife = 40;


int isOccupiedByEnemy(int x, int y)     //Generalizable, it is possible to return another value for other objects, i.e. return 2 if it is occupied by player.
{
    if(space[y][x].enemyId == -1) return 0;
    return 1;
}

bool canPutEnemy(int x, int y, int level)
{
    int positionsNumber = 11;
    if(level == 3) positionsNumber = 9;

    if(x<leftLimit || x>rightLimit) return false;                 
    for (int i = 0; i < positionsNumber; i++)
    {
        if(level == 3)
        {
            if (isOccupiedByEnemy(x + enemyPosLv3[i].x, y + enemyPosLv3[i].y)) return false;

        }
        else if(level == 4)
        {
            if(isOccupiedByEnemy(x + enemyPosBoss[i].x, y + enemyPosBoss[i].y)) return false;
        }
        else
        {
            if(isOccupiedByEnemy(x + enemyPosLv1[i].x, y + enemyPosLv1[i].y)) return false;
        }
    }
    return true;      
}

void enemiesInit()
{
    switch (level)
    {
    case 1:
        levelSpawnsNumber = 12;
        break;
    
    case 2:
        levelSpawnsNumber = 23;
        break;

    case 3:
        levelSpawnsNumber = 28;
        break;
    case 4:
        levelSpawnsNumber = 34;
        break;
    case 5:
        levelSpawnsNumber = 1000000;
        break;
    default:
        break;
    }

    numberEnemiesDefeated = 0;
    numberEnemiesSpawned = 0;

    switch (level)
    {
    case 1:
        cap = 5;
        break;
    case 2:
        cap = 6;
        break;
    case 3:
        cap = 6;
        break;
    case 4:
        cap = 7;    
        break;      
    case 5:
        cap = 11;    
        break;     
    default:
        break;
    }

    bossLife = 20;
    srand(time(NULL));

    assignenemyPos();

    for (int i = 0; i < numberOfEnemies; i++)
    {
        enemies[i].coreX = 0;
        enemies[i].coreY = 0;
        enemies[i].index = 0;
        enemies[i].isAlive = 0;
    }

    for (int i = 0; i < zonesNumber; i++)
    {
        defeatedEnemiesPerZone[i] = 0;
    }
    
    
    for (int i = 0; i < cap; i++)
    {
        generateEnemy(i);
    }

    createThread(enemiesManagment);
    //pthread_join(threads[auxThreadPointer], NULL);
}

void generateEnemy(int index)
{
    if(level == 5 && numberEnemiesSpawned == 0)
    {
    
        enemies[7].level = 4;
        enemies[7].coreX = 83;
        enemies[7].coreY = 2;
        enemies[7].isAlive = 1;
        enemies[7].index = 7;
        enemies[7].shotCooldown = 10;
        enemies[7].movementDirection = left;
        enemies[7].positionsArray = enemyPosBoss;
        enemies[7].positionsNumber = sizeof(enemyPosBoss)/sizeof(enemyPosBoss[0]);
        numberEnemiesSpawned ++;
        draw(132, anchoMapa + 3, "Captain Eggplant", 5);
        setEnemy(enemies[7]);
        drawEnemy(enemies[7]);
    
    
        return;
    }
    
    if(level >= 3 && numberEnemiesSpawned == 0 && level != 5)
    {
        for (int i = cap; i < cap + level + 2; i++)
        {
            if(enemies[i].isAlive == 1) continue;

            int x;
            do
            {
                x = rand()%rightLimit + leftLimit;
            }while(!canPutEnemy(x, 1, 3));

            enemies[i].level = 3;
            enemies[i].coreX = x;
            enemies[i].coreY = 1;
            enemies[i].isAlive = 1;
            enemies[i].index = i;
            enemies[i].shotCooldown = 2;
            enemies[i].movementDirection = left;
            enemies[i].positionsArray = enemyPosLv3;
            enemies[i].positionsNumber = sizeof(enemyPosLv3)/sizeof(enemyPosLv3[0]);

            if(x <= zoneMarker1) enemies[i].zone = 0;
            else if(x <= zoneMarker2) enemies[i].zone = 1;
            else enemies[i].zone = 2;
            numberEnemiesSpawned++;
            setEnemy(enemies[i]);
            drawEnemy(enemies[i]);
        }
    }

    if(numberEnemiesSpawned >= levelSpawnsNumber) return;

    int spawnPosY = 4;
    if(level == 5) spawnPosY = 8;
    for (int i = 0; i < cap; i++)
    {
        
        if(enemies[i].isAlive == 1) continue;

        int x;
        do
        {
            x = rand()%rightLimit + leftLimit;
        }while(!canPutEnemy(x, spawnPosY, 1));

        enemies[i].level = 1;
        enemies[i].coreX = x;
        enemies[i].coreY = spawnPosY;
        enemies[i].isAlive = 1;
        enemies[i].index = i;
        enemies[i].shotCooldown = 2;
        enemies[i].movementDirection = down;
        enemies[i].positionsArray = enemyPosLv1;
        enemies[i].positionsNumber = sizeof(enemyPosLv1)/sizeof(enemyPosLv1[0]);

        if(x <= zoneMarker1) enemies[i].zone = 0;
        else if(x <= zoneMarker2) enemies[i].zone = 1;
        else enemies[i].zone = 2;
        
        if(level >= 2 && numberEnemiesSpawned%3 == 0 && numberEnemiesSpawned > 0) enemies[i].level = 2; 
        numberEnemiesSpawned++;
        setEnemy(enemies[i]);
        drawEnemy(enemies[i]);
    }
}

int genRandTeleportPosition(int leftBorder, int rightBorder, enemy e)
{
    int x;
    do
    {
        x = rand()%rightBorder + leftBorder;
    }while(!canPutEnemy(x, e.coreY + 1, e.level));

    return x;
}

void* enemiesManagment(void* thr)           // Manages the enemies movement.
{
    while (1)
    {
        generateEnemy(0);    

        
        pthread_mutex_lock(&lock);

        for (int j = 0; j < numberOfEnemies; j++)
        {
            enemy *e = &enemies[j];

            if(e->index == -1 || e->isAlive == 0) continue;
            if(e->level == 2 && e->coreY%6 == 0 && e->coreY <= 25)
            {
                enemyLv2Ability(enemies[j]);
            }
            else if(e->level == 4)
            {
                if(e->shotCooldown == 0){generateBossShoot(e->index, e->coreX, e->coreY); e->shotCooldown = 10;}
                else(e->shotCooldown --);
                moveBoss(*e);
            }
            else
            {
                if(e->level == 3)
                {
                    if(e->shotCooldown == 0){enemyLv3Ability(*e); e->shotCooldown = 3;}
                    else(e->shotCooldown --);
                }
                moveEnemy(j, e->movementDirection);
            }
            
            drawEnemy(*e);
        }
        refresh();
        pthread_mutex_unlock(&lock);
        
        if(restart == true) pthread_exit(NULL);
        
        napms(500);
    }
}

void cleanEnemy(enemy e)             // Cleans an enemy out of the screen.
{
    int ex = e.coreX;
    int ey = e.coreY;

    //pthread_mutex_lock(&lock);
    
    attron(COLOR_PAIR(3));
    for (int i = 0; i < e.positionsNumber; i++)        // The positions of an enemy.
    {
        mvaddch(ey + e.positionsArray[i].y, ex + e.positionsArray[i].x, ' ');
        space[ey + e.positionsArray[i].y][ex + e.positionsArray[i].x].enemyId = -1;
    }
    
    attroff(COLOR_PAIR(3));
    //refresh();
    //pthread_mutex_unlock(&lock);
}

void setEnemy(enemy e)
{
    int x = e.coreX;
    int y = e.coreY;

    for (int i = 0; i < e.positionsNumber; i++)        // The positions of an enemy.
    {
        if(space[y + e.positionsArray[i].y][x + e.positionsArray[i].x].occupiedByPlayer)
        {
            space[y + e.positionsArray[i].y][x + e.positionsArray[i].x].enemyId = e.index;
            pthread_mutex_unlock(&lock);
            destroyEnemy(x + e.positionsArray[i].x, y + e.positionsArray[i].y);
            drawPlayer();
            damageLife();
            pthread_mutex_lock(&lock);
            return;
        }
    }

    for (int i = 0; i < e.positionsNumber; i++)
    {
        space[y + e.positionsArray[i].y][x + e.positionsArray[i].x].enemyId = e.index;
    }

}

void moveEnemy(int enemyId, int direction)
{
    enemy *e = &enemies[enemyId];
    cleanEnemy(*e);
    int x = e->coreX;
    int y = e->coreY;


    switch (direction)
    {
    case 0:
        if(!canPutEnemy(x - 3, y, e->level))
        {
            if(e->level == 3 || e->level == 4) e->movementDirection = right;
            break;
        }
        e->coreX += -3;
        break;
    case 1:
        if(x + 3 > largoMapa - 3 || !canPutEnemy(x + 3, y, e->level))
        {
            if(e->level == 3 || e->level == 4) e->movementDirection = left;
            break;
        }
        e->coreX += 3;
        break;
    case 2:
        if(y - 1 < 1 || !canPutEnemy(x, y - 1, e->level)) break;
        e->coreY += -1;
        break;
    case 3:
        if(y + 1 > anchoMapa - 4) restart = true;
        if(!canPutEnemy(x, y + 1, e->level)) break;
        e->coreY += 1;
        break;
    default:
        break;
    }
    setEnemy(*e);
}

void moveBoss(enemy boss)
{
    enemy *e = &enemies[boss.index];
    int index = e->index;
    cleanEnemy(*e);

    if(e->movementDirection == left)
    {
        if(e->coreX - 5 <= leftLimit || !canPutEnemy(e->coreX - 5, e->coreY, e->level)) e->movementDirection = right;
    }
    else if(e->movementDirection == right)
    {
        if(e->coreX + 20 >= rightLimit || !canPutEnemy(e->coreX + 20, e->coreY, e->level)) e->movementDirection = left;
    }

    if(e->movementDirection == left) enemies[index].coreX = enemies[index].coreX - 5;
    if(e->movementDirection == right) enemies[index].coreX = enemies[index].coreX + 5;

    setEnemy(enemies[index]);
}

void drawEnemy(enemy e)
{
    //pthread_mutex_lock(&lock);

    if(e.isAlive == 0) return;
    
    if(e.level == 2) attron(COLOR_PAIR(8)); else if(e.level == 1) attron(COLOR_PAIR(4)); else attron(COLOR_PAIR(10)); 

    if(e.level == 4)
    {
        for (int i = 0; i < e.positionsNumber; i++)        // The positions of an enemy.
        {   
            
            if(i > 74) attron(COLOR_PAIR(11));
            else if(i == 17 || i == 18 || i == 27 || i == 26 || i == 32 || i == 33) attron(COLOR_PAIR(13));
            else attron(COLOR_PAIR(12));
            mvaddch(e.coreY + e.positionsArray[i].y, e.coreX + e.positionsArray[i].x, ' ');
            if(i > 74) attron(COLOR_PAIR(11));
            else if(i == 17 || i == 18 || i == 28 || i == 29 || i == 32 || i == 33 || i == 43 || i == 44) attron(COLOR_PAIR(13));
            else attron(COLOR_PAIR(12));
        }   
        return;
    }
    for (int i = 0; i < e.positionsNumber; i++)        // The positions of an enemy.
    {
        if(e.level < 3 && (i == 8 || i == 10))
        {
            if(e.level == 2)
            {
                attron(COLOR_PAIR(9));
                mvaddch(e.coreY + e.positionsArray[i].y, e.coreX + e.positionsArray[i].x, ' ');
                attroff(COLOR_PAIR(9));
            }
            else if(e.level == 1)
            {
                attron(COLOR_PAIR(1));
                mvaddch(e.coreY + e.positionsArray[i].y, e.coreX + e.positionsArray[i].x, ' ');
                attroff(COLOR_PAIR(1));
            }

            if(e.level == 2) attron(COLOR_PAIR(8)); else if(e.level == 1) attron(COLOR_PAIR(4)); else attron(COLOR_PAIR(10)); 
            continue;
        }    
        mvaddch(e.coreY + e.positionsArray[i].y, e.coreX + e.positionsArray[i].x, ' ');
    }
    if(e.level == 2) attroff(COLOR_PAIR(8));
    attroff(COLOR_PAIR(4));
    
    //refresh();
    //pthread_mutex_unlock(&lock);
}

void destroyEnemy(int x, int y)                     // Cleans an enemy and set it dead, frees its position from the enemies array.
{
    //if(space[y][x].occupierEnemy == NULL) return;

    //enemy * e = space[y][x].occupierEnemy;
    //int coreX = e->coreX;
    //int coreY = e->coreY;
    
    int index = space[y][x].enemyId;
    enemy e = enemies[index];
    int coreX = e.coreX;
    int coreY = e.coreY;

    if(e.level == 4 && bossLife >= 1)
    {
        damageBossLife();
        
        if(bossLife != 0) return;
    }
    aliveEnemies[index] = false;

    for (int i = 0; i < e.positionsNumber; i++)        // The positions of an enemy.
    {
        draw(coreX + e.positionsArray[i].x, coreY + e.positionsArray[i].y, " ", 3);
        space[coreY + e.positionsArray[i].y][coreX + e.positionsArray[i].x].enemyId = -1;
    }

    enemies[index].isAlive = 0;

    numberEnemiesDefeated ++;
    

    defeatedEnemiesPerZone[e.zone] ++;

    if(numberEnemiesDefeated >= levelSpawnsNumber || bossLife == 0)      // Change of Level
    {
        winner = true;
        level++;
        nextLevel = true;
        restart = true;
    }     

}

void enemyLv2Ability(enemy e)
{
    int min = maxEnemiesNumber + 1;
    int index = 0;

    for (int i = 0; i < zonesNumber; i++)
    {
        if(defeatedEnemiesPerZone[i] < min)
        {
            min = defeatedEnemiesPerZone[i];
            index = i;
        }  
    }

    int x;
    switch (index)
    {
    case 0:
        x = genRandTeleportPosition(leftLimit, zoneMarker1, e);
        break;
    case 1:
        x = genRandTeleportPosition(zoneMarker1, zoneMarker2, e);
        break;
    case 2:
        x = genRandTeleportPosition(zoneMarker2, rightLimit, e);
        break;    
    default:
        break;
    }

    teleportEnemy(e.index, x, e.coreY + 1);
}

void enemyLv3Ability(enemy e)
{
    generateShoot(e.index);
}

void teleportEnemy(int index, int x, int y)
{

    enemies[index].abilityUsed = true;

    cleanEnemy(enemies[index]);

    enemies[index].coreX = x;
    enemies[index].coreY = y;

    setEnemy(enemies[index]);
}

void assignenemyPos()
{
    // Level 1 and 2 enemy positions
    enemyPosLv1[0].x = enemyPosLv1[6].x = enemyPosLv1[9].x = 0;
    enemyPosLv1[2].x = enemyPosLv1[10].x = 1;
    enemyPosLv1[8].x = enemyPosLv1[1].x = -1;
    enemyPosLv1[7].x = enemyPosLv1[4].x = 2;
    enemyPosLv1[3].x = enemyPosLv1[5].x = -2;

    enemyPosLv1[0].y = enemyPosLv1[1].y = enemyPosLv1[2].y = enemyPosLv1[3].y = enemyPosLv1[4].y = 0;
    enemyPosLv1[5].y = enemyPosLv1[6].y = enemyPosLv1[7].y = 1;
    enemyPosLv1[8].y = enemyPosLv1[9].y = enemyPosLv1[10].y = -1;


    // Level 3 enemy positions
    
    enemyPosLv3[0].x = enemyPosLv3[7].x = enemyPosLv3[5].x = 0;
    enemyPosLv3[2].x = enemyPosLv3[8].x = 1;
    enemyPosLv3[6].x = enemyPosLv3[1].x = -1;
    enemyPosLv3[4].x = 2;
    enemyPosLv3[3].x = -2;

    enemyPosLv3[0].y = enemyPosLv3[1].y = enemyPosLv3[2].y = enemyPosLv3[3].y = enemyPosLv3[4].y = 0;
    enemyPosLv3[5].y = 1;
    enemyPosLv3[6].y = enemyPosLv3[7].y = enemyPosLv3[8].y = -1;

    // Boss positions

    int column = 0;

    for (int i = 0; i < 75; i++)
    {
        enemyPosBoss[i].x = i%15;
        if(i < 15)enemyPosBoss[i].y = 0;
        else if(i < 30)enemyPosBoss[i].y = 1;
        else if(i < 45)enemyPosBoss[i].y = 2;
        else if(i < 60)enemyPosBoss[i].y = 3;
        else if(i < 75)enemyPosBoss[i].y = 4;
    }

    enemyPosBoss[75].y = enemyPosBoss[76].y = enemyPosBoss[77].y = enemyPosBoss[78].y = enemyPosBoss[79].y = -1;
    enemyPosBoss[80].y = enemyPosBoss[81].y = enemyPosBoss[82].y = -2;

    enemyPosBoss[75].x = enemyPosBoss[80].x = 5;
    enemyPosBoss[76].x = 6;
    enemyPosBoss[77].x = enemyPosBoss[81].x = 7;
    enemyPosBoss[78].x = 8;
    enemyPosBoss[79].x = enemyPosBoss[82].x = 9;
}

void damageBossLife()
{
    bossLife --;
    
    for (int i = 130; i < 150; i++)
    {
        if(i < 130 + bossLife) draw(i, anchoMapa + 2, " ", 12);
        else draw(i, anchoMapa + 2, " ", 3);
    }
}