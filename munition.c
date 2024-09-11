#include"munition.h"

void munition()
{
    createThread(reload);
    //pthread_join(threads[auxThreadPointer], NULL);
}

void* reload(void * th)
{
    while (1)
    {
        if(player.munition < maxMunition)
        {
            player.munition ++;
            drawMunition();
        }
        if(restart == true) pthread_exit(NULL);
        napms(2000);
    }
}