#include"shoot.h"
#include"player.h"
#include"enemies.h"
#include"map.h"

struct shoot shoots[200];
int shootsNumber = sizeof(shoots)/sizeof(shoots[0]);

void generateShoot(int shooterId)
{
    struct shoot s;
    s.active = 1;
    s.shooterId = shooterId;

    if(shooterId == -1)
    {
        player.munition --;
        drawMunition();
        s.x = player.x;
        s.y = player.y - 2;
    }
    else
    {
        s.x = enemies[shooterId].coreX;
        s.y = enemies[shooterId].coreY + 3;
    }

    addShoot(s);
}

void generateBossShoot(int enemyId, int x, int y)
{
    struct shoot s[5];
    
    s[0].x = enemyPosBoss[48].x + x;
    s[0].y = enemyPosBoss[48].y + y;
    s[1].x = enemyPosBoss[51].x + x;
    s[1].y = enemyPosBoss[51].y + y;
    s[2].x = enemyPosBoss[54].x + x;
    s[2].y = enemyPosBoss[54].y + y;
    s[3].x = enemyPosBoss[57].x + x;
    s[3].y = enemyPosBoss[57].y + y;


    for (int i = 0; i < 4; i++)
    {
        s[i].active = 1;
        s[i].shooterId = enemyId;
        addShoot(s[i]);
    }
    
}


void addShoot(struct shoot s)
{
    //pthread_mutex_lock(&shootLock);

    for (int i = 0; i < shootsNumber; i++)
    {
        if(shoots[i].active == 0)
        {
            shoots[i] = s;
            break;
        }
    }
    //pthread_mutex_unlock(&shootLock);
}

void shootsInit()
{
    for (int i = 0; i < shootsNumber; i++)
    {
        shoots[i].x = 0;
        shoots[i].y = 0;
        shoots[i].active = 0;
    }

    createThread(manageShoot);
    //pthread_join(threads[auxThreadPointer], NULL);

}

void* manageShoot(void * thr)
{
    while (1)
    {
        pthread_mutex_lock(&shootLock);
        for (int i = 0; i < shootsNumber; i++)
        {
            struct shoot s =  shoots[i];
            if(s.y < 0) cleanPosition(s.x, s.y + 1);
            if(s.y >= anchoMapa - 1) cleanPosition(s.x, s.y - 1);

            if (s.active == 1)
            {   
                if (s.shooterId == -1)
                {
                    if(s.y != player.y - 2) cleanPosition(s.x, s.y + 1);        //Depends of the player's dimensions. Erase  previous position
                    drawShoot(s);
                    
                    if(space[s.y][s.x].enemyId != -1)
                    {
                        destroyEnemy(s.x, s.y);
                        shoots[i].active = 0;
                        continue;
                    }
                    shoots[i].y = shoots[i].y - 1;
                    if(shoots[i].y < 0) shoots[i].active = 0;   
                }
                else
                {
                    if(space[s.y - 1][s.x].enemyId == -1)cleanPosition(s.x, s.y - 1);       // Erase  previous shot position
                    if(space[s.y][s.x].enemyId == -1)drawShoot(s);      // Do not draw if is friend fire between enemies.

                    if(space[s.y][s.x].occupiedByPlayer)
                    {
                        damageLife();
                        shoots[i].active = 0;
                        continue;
                    }
                    shoots[i].y = shoots[i].y + 1;
                    if(shoots[i].y >= anchoMapa - 1) shoots[i].active = 0;  
                }
            }
        }

        pthread_mutex_lock(&lock);
        refresh();
        pthread_mutex_unlock(&lock);

        pthread_mutex_unlock(&shootLock);
        if(restart == true) pthread_exit(NULL);

        napms(25);
    }
}

void drawShoot(struct shoot s)
{
    pthread_mutex_lock(&lock);
    attron(COLOR_PAIR(2));
    mvaddch(s.y, s.x, ' ');
    attroff(COLOR_PAIR(2));
    //refresh();
    pthread_mutex_unlock(&lock);
}

