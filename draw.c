
void draw()
{
    while (1)
    {
        clear();

        drawPlayer();
        drawLifes();
        drawMunition();

        
        for (int i = 0; i < numberOfEnemies; i++)
        {
            if(enemies[i].index == -1 || enemies[i].isAlive == 0) continue;
            drawEnemy(enemies[i]);
        }

        for (int i = 0; i < shootsNumber; i++)
        {
            if(shoots[i].active == 0) continue;
            drawShoot(shoots[i]);
        }

        refresh();
        doupdate();
        napms(40);
    }
}
