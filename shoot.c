#include"shoot.h"

void generateShoot()
{
    player.munition --;
    drawMunition();
    
    struct shoot s;
    s.x = player.x;
    s.y = player.y - 2;
    s.active = 1;

    addShoot(s);
}

void addShoot(struct shoot s)
{
    pthread_mutex_lock(&shootLock);

    for (int i = 0; i < shootsNumber; i++)
    {
        if(shoots[i].active == 0)
        {
            shoots[i] = s;
            break;
        }
    }
    pthread_mutex_unlock(&shootLock);
}

void shootsInit()
{
    for (int i = 0; i < shootsNumber; i++)
    {
        shoots[i].x = 0;
        shoots[i].y = 0;
        shoots[i].active = 0;
    }

    
    threadPointer += 1;
    usingThread[threadPointer] = true;
    int auxThreadPointer = threadPointer;
    pthread_create(&threads[threadPointer], NULL, manageShoot, NULL);
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

            if (s.active == 1)
            {   
                if(s.y != player.y - 2) cleanPosition(s.x, s.y + 1);        //Depends of the player's dimensions.

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

