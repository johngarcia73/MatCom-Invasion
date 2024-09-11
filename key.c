#include"key.h"

void* keyListener(void* t)        
{   
    int key;
    int step = 0;
    while(1)
    {
        pthread_mutex_lock(&lock);

        key = getch();
        flushinp();

        pthread_mutex_unlock(&lock);

        if(key == 32)
        {
            if(player.munition > 0 && player.y > 1) generateShoot(-1);
        }
        else
        {
            switch (key)
            {
                case KEY_LEFT:
                    erasePlayer();
                    if (player.x > 2) movePlayer(left);
                    break;
                case KEY_RIGHT:
                    erasePlayer();
                    if (player.x < largoMapa - 3) movePlayer(right);
                    break;
                case KEY_UP:
                    erasePlayer();
                    if (player.y > 1) movePlayer(up);
                    break;
                case KEY_DOWN:
                    erasePlayer();
                    if (player.y < anchoMapa - 2) movePlayer(down);
                    break;
                default:
                    break;    
            }
            drawPlayer();
        }

        if(restart == true) pthread_exit(NULL);
        napms(50);
        
    }  

}
