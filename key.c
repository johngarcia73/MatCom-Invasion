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
        switch (key)
        {
            case KEY_LEFT:
                if (player.x > 2)
                {
                    pthread_mutex_unlock(&lock);
                    erasePlayer();
                    movePlayer(left);
                    drawPlayer();
                }
                break;
            case KEY_RIGHT:
                if (player.x < largoMapa - 3)
                {
                    pthread_mutex_unlock(&lock);
                    erasePlayer();
                    movePlayer(right);
                    drawPlayer();
                }
                break;
            case KEY_UP:
                if (player.y > 1)
                {   
                    pthread_mutex_unlock(&lock);
                    erasePlayer();
                    movePlayer(up);
                    drawPlayer();
                }
                break;
            case KEY_DOWN:    
                if (player.y < anchoMapa - 2)
                {
                    pthread_mutex_unlock(&lock);
                    erasePlayer();
                    movePlayer(down);
                    drawPlayer();
                }
                break;
            case 32:
                pthread_mutex_unlock(&lock);
                if(player.munition > 0 && player.y > 1) generateShoot();
                break;

            default:
                pthread_mutex_unlock(&lock);
                break;    
        }

        if(restart == true) pthread_exit(NULL);
        napms(50);
        
    }  

}
