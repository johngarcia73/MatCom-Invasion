#include"control.h"

void killAll()
{
    for (int i = 0; i < threadPointer; i++)
    {
        pthread_cancel(threads[i]);
    }
    
}