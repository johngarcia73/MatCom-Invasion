#include"shoot.h"

void generateShoot()
{
    pthread_t thread;

    thread = pthread_create(&thread, NULL, shootThread, NULL);

    //WaitForSingleObject(thread, INFINITE);
    pthread_join(thread, NULL);

}

void* shootThread(void *  thr)
{
    struct shoot s;
    s.ascii = ' ';
    s.x = player.x;
    s.y = player.y - 2;

    manageShoot(s);
}

void manageShoot(struct shoot s)
{
    while (s.y >= 0)
    {
        drawShoot(s);
        //map[s.y][s.x] = s.ascii;
        if(space[s.y][s.x].enemyId != -1)
        {
            destroyEnemy(s.x, s.y);
            return;
        }

        napms(50);
        cleanPosition(s.x, s.y);
        s.y = s.y - 1; 
    }
    
    cleanPosition(s.x, s.y);
    pthread_exit(shootThread);
}

void drawShoot(struct shoot s)
{
    attron(COLOR_PAIR(2));
    mvaddch(s.y, s.x, s.ascii);
    attroff(COLOR_PAIR(2));
    refresh();
}

