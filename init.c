#include"init.h"

void init()   //Initializes the map with start positions.
{
    winner = false;
    clear();
    
    for (int i = 0; i < anchoMapa; i++)
    {
        for (int j = 0; j < largoMapa; j++)
        {
            struct tile t;
            t.posX = j;
            t.posY = i;
            t.enemyId = -1;
            t.occupiedByPlayer = false;
            t.shotId = -1;
            space[i][j] = t;
        }
    }

    switch (level)
    {
    case 1:
        maxMunition = 18;
        break;
    case 2:
        maxMunition = 26;
        break;
    case 3:
        maxMunition = 35;
        break;
    case 4:
        maxMunition = 44;
        break;
    case 5:
        maxMunition = 50;
        break;
    default:
        break;
    }

    player.x = (int)largoMapa/2;
    player.y = anchoMapa - 3;
    setPlayer();
    player.lifes = 3;
    player.munition = maxMunition;
    

    shipPositions[0].x = 0;
    shipPositions[0].y = 0;
    shipPositions[1].x = 1;
    shipPositions[1].y = 0;
    shipPositions[2].x = -1;
    shipPositions[2].y = 0;
    shipPositions[3].x = 0;
    shipPositions[3].y = -1;
    shipPositions[4].x = 2;
    shipPositions[4].y = 0;
    shipPositions[5].x = -2;
    shipPositions[5].y = 0;
    shipPositions[6].x = 2;
    shipPositions[6].y = 1;
    shipPositions[7].x = -2;
    shipPositions[7].y = 1;

    drawLifes();
    drawLevel();
    drawPlayer();
    drawMunition();
    drawGround();
}

