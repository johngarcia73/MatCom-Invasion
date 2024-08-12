#include"game.h"

void game();


void game()
{   
    level = 1;
    
    while(1)
    {
        init();

        enemiesInit();

        shootsInit();

        munition();

        threadPointer += 1;
        int auxThreadPointer = threadPointer;
        usingThread[threadPointer] = true;
        pthread_create(&threads[threadPointer], NULL, keyListener, NULL);
        //pthread_join(threads[auxThreadPointer], NULL);
        
        while (1)
        {
            if(restart)
            { 
                napms(1000);
                killAll();
                restart = false;

                break;
            }
        }
        if(!nextLevel) break;
        nextLevel = false;
    }

    //clear();
}

void endGame()
{
    killAll();
    restart = true;
    return;
}