struct ship
{
    int x;
    int y;
    int lifes;
    int munition;
};

struct ship player;

struct position shipPositions[8];
int playerPositionsNumber = sizeof(shipPositions)/sizeof(shipPositions[0]);

#define maxMunition 20

void drawPlayer();
void setPlayer();
void erasePlayer();
void damageLife();
void drawMunition();
void drawLifes();
void movePlayer(int direction);