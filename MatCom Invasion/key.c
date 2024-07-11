void keyListener()        //Calls Draw function and identifies if user pressed -> or <-, and updates the ship position.
{
    int key;
    int step = 0;
    while(1)
    {
        key = getch();
        switch (key)
        {
            case KEY_LEFT:
                if (player.x > 2)
                {
                    *space[player.y][player.x].mapTile = ' ';
                    erasePlayer();
                    setPlayer(player.x - 1, player.y);
                    drawPlayer();
                }
                break;
            case KEY_RIGHT:
                if (player.x < largoMapa - 3)
                {
                    *space[player.y][player.x].mapTile = ' ';
                    erasePlayer();
                    setPlayer(player.x + 1, player.y);
                    drawPlayer();
                }
                break;
            case KEY_UP:
                if (player.y > 1)
                {   
                    *space[player.y][player.x].mapTile = ' ';
                    erasePlayer();
                    setPlayer(player.x, player.y - 1);
                    drawPlayer();
                }
                break;
            case KEY_DOWN:    
                if (player.y < anchoMapa - 2)
                {
                    *space[player.y][player.x].mapTile = ' ';
                    erasePlayer();
                    setPlayer(player.x, player.y + 1);
                    drawPlayer();
                }
                break;
            
            case 32:
                generateShoot();
                break;

            default:
                break;    
        }

        //*space[player.y][player.x].mapTile = player.ascii;

    
        napms(50);
        
    }  

}
