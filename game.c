#include"game.h"

void game()
{       
    level = 1;

    while(1)
    {
        init();

        enemiesInit();

        shootsInit();

        munition();

        createThread(keyListener);
        
        while (1)
        {
            if(restart)
            { 
                play = false;
                napms(1100);
                killAll();
                restart = false;

                break;
            }
        }
        if(!nextLevel || level > totalLevels) break;
        nextLevel = false;
    }

    if(level >= totalLevels && winner)
    {
        nextLevel = false;
        winnerScreen();
    }
    //clear();
}