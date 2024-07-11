struct ship
{
    char ascii;
    int x;
    int y;
    int lifes;
};

struct ship player;

struct position shipPositions[8];

void drawPlayer();
void setPlayer(int x,int y);
void erasePlayer();
void damageLife();