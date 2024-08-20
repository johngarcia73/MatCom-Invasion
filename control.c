#include"control.h"

pthread_t threads[100];
bool usingThread[100];
int threadPointer = 0;
bool restart = false;

void killAll()
{
    for (int i = 1; i <= threadPointer; i++)
    {
       
        pthread_join(threads[i], NULL);
    }
    threadPointer = 0;
}