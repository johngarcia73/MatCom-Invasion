void init()   //Initializes the map with start positions.
{
    for (int i = 0; i < anchoMapa; i++)
    {
        for (int j = 0; j < largoMapa; j++)
        {
            struct tile t;
            t.posX = j;
            t.posY = i;
            t.occupierEnemy = NULL;
            t.enemyId = -1;
            t.occupiedByPlayer = false;
            t.mapTile = &map[i][j];
            space[i][j] = t;
        }
    }

    player.ascii = ' ';
    player.x = (int)largoMapa/2;
    player.y = anchoMapa - 2;
    player.lifes = 3;
    *space[player.y][player.x].mapTile = player.ascii;

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

    attron(COLOR_PAIR(5));
    mvprintw(anchoMapa + 2, 1, "Lifes: %d", player.lifes);
    attroff(COLOR_PAIR(5));
    refresh();

    drawPlayer();
}

