#include"enemies.h"
#include<time.h>

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
        if (isOccupiedByEnemy(x + p[i].x, y + p[i].y)) return false;
        
    }
    return true;      
}

void enemiesInit()
{
    srand(time(NULL));

    p[0].x = 0;     //Positions occupied by en enemy.
    p[0].y = 0;
    p[1].x = 1;
    p[1].y = 0;
    p[2].x = -1;
    p[2].y = 0;
    p[3].x = 2;
    p[3].y = 0;
    p[4].x = -2;
    p[4].y = 0;
    p[5].x = 0;
    p[5].y = -1;
    p[6].x = 1;
    p[6].y = -1;
    p[7].x = -1;
    p[7].y = -1;
    p[8].x = -1;
    p[8].y = 1;
    p[9].x = 0;
    p[9].y = 1;
    p[10].x = 1;
    p[10].y = 1;
    //
    p[11].x = 2;
    p[11].y = 1;
    p[12].x = -2;
    p[12].y = 1;
    p[13].x = 0;
    p[13].y = 2;
    p[14].x = 2;
    p[14].y = 2;
    p[15].x = -2;
    p[15].y = 2;


    for (int i = 0; i < numberOfEnemies; i++)
    {
        generateEnemy(i);
    }

    usingThread[threadPointer] = true;
    int auxThreadPointer = threadPointer;
    pthread_create(&threads[threadPointer++], NULL, enemiesManagment, NULL);
    
    //pthread_join(threads[auxThreadPointer], NULL);
}

void generateEnemy(int i)
{
    int random;
    do
    {
        random = (rand() % largoMapa); 
        
    } while (!canPutEnemy(random, 1));

    enemies[i].coreX = random;
    enemies[i].coreY = 1;
    enemies[i].isAlive = 1;
    enemies[i].index = i;
    setEnemy(&enemies[i]);
    numberEnemiesSpawned++;
    
}

void* enemiesManagment(void* thr)
{
    while (1)
    {        
        for (int i = 0; i < numberOfEnemies; i++)
        {
            if(enemies[i].index == -1 || enemies[i].isAlive == 0)
            {
                if(numberEnemiesSpawned == maxEnemiesNumber) continue;
                generateEnemy(i);
                break;
            }
        }
        
        for (int i = 0; i < 5; i++)
        {
            for (int i = 0; i < numberOfEnemies; i++)
            {      
                if(enemies[i].index == -1 || enemies[i].isAlive == 0) continue;
                moveEnemy(i, right);
                drawEnemy(&enemies[i]);
            }
            napms(800);
        }
        
        
        for (int i = 0; i < 5; i++)
        {
            for (int i = 0; i < numberOfEnemies; i++)
            {
                if(enemies[i].index == -1 || enemies[i].isAlive == 0) continue;
                moveEnemy(i, left);
                
                drawEnemy(&enemies[i]);
            }
            napms(800);
        }
    }
}

void cleanEnemy(struct enemy * e)
{
    int ex = e->coreX;
    int ey = e->coreY;

    attron(COLOR_PAIR(3));
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        mvaddch(e->coreY + p[i].y, e->coreX + p[i].x, ' ');
        space[ey + p[i].y][ex + p[i].x].enemyId = -1;
    }
    
    attroff(COLOR_PAIR(3));
    refresh();
}

void setEnemy(struct enemy * e)
{
    int x = e->coreX;
    int y = e->coreY;
    
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        space[y + p[i].y][x + p[i].x].occupierEnemy = e;
        space[y + p[i].y][x + p[i].x].enemyId = e->index;
    }
}

void moveEnemy(int enemyId, int direction)
{
    cleanEnemy(&enemies[enemyId]);
    int x = enemies[enemyId].coreX;
    int y = enemies[enemyId].coreY;


    switch (direction)
    {
    case 0:
        if(x - 1 < 2 || !canPutEnemy(x - 1, y)) break;
        enemies[enemyId].coreX += -1;
        setEnemy(&enemies[enemyId]);
        break;
    case 1:
        if(x + 1 > largoMapa - 3 || !canPutEnemy(x + 1, y)) break;
        enemies[enemyId].coreX += 1;
        setEnemy(&enemies[enemyId]);
        break;
    case 2:
        if(y - 1 < 1 || !canPutEnemy(x, y - 1)) break;
        enemies[enemyId].coreY += -1;
        setEnemy(&enemies[enemyId]);
        break;
    case 3:
        if(y + 1 > anchoMapa - 2 || !canPutEnemy(x, y + 1)) break;
        enemies[enemyId].coreY += 1;
        setEnemy(&enemies[enemyId]);
        break;
    default:
        break;
    }
}

void drawEnemy(struct enemy * e)
{
    attron(COLOR_PAIR(4));
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        if(i == 6 || i == 7)
        {
            attron(COLOR_PAIR(1));
            mvaddch(e->coreY + p[i].y, e->coreX + p[i].x, ' ');
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(4));
            continue;
        }    
        mvaddch(e->coreY + p[i].y, e->coreX + p[i].x, ' ');
    }
    attroff(COLOR_PAIR(4));
    refresh();
}

void destroyEnemy(int x, int y)
{
    //if(space[y][x].occupierEnemy == NULL) return;

    //struct enemy * e = space[y][x].occupierEnemy;
    //int coreX = e->coreX;
    //int coreY = e->coreY;
    
    int index = space[y][x].enemyId;
    struct enemy e = enemies[index];
    int coreX = e.coreX;
    int coreY = e.coreY;

    attron(COLOR_PAIR(3));
    for (int i = 0; i < enemyPositionsNumber; i++)        // The positions of an enemy.
    {
        mvaddch(coreY + p[i].y, coreX + p[i].x, ' ');
        space[coreY + p[i].y][coreX + p[i].x].enemyId = -1;
    }

    
    attroff(COLOR_PAIR(3));
    refresh();

    //space[coreY][coreX].occupierEnemy = NULL;
    //space[coreY-1][coreX].occupierEnemy = NULL;
    //space[coreY][coreX-1].occupierEnemy = NULL;
    //space[coreY][coreX+1].occupierEnemy = NULL;

    //e->isAlive = 0;

    enemies[index].isAlive = 0;
}