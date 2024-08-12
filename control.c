#include"control.h"

void killAll()
{
    for (int i = 1; i <= threadPointer; i++)
    {
       
        pthread_join(threads[i], NULL);
    }
    threadPointer = 0;
}

bool restart = false;