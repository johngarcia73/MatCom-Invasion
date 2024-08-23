#include"munition.h"

void munition()
{
    threadPointer += 1;
    usingThread[threadPointer] = true;
    int auxThreadPointer = threadPointer;
    pthread_create(&threads[threadPointer], NULL, reload, NULL);
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
        sleep(3);
    }
}