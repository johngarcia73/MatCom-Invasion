struct enemy
{
    int coreX;
    int coreY;
    int isAlive;
    int index;
};

#define left 0
#define right 1
#define up 2
#define down 3
#define maxEnemiesNumber 10

struct enemy enemies[5];
int numberOfEnemies = sizeof(enemies)/sizeof(enemies[0]);
struct position p[16];
int enemyPositionsNumber = sizeof(p)/sizeof(p[0]);
int numberEnemiesSpawned = 0;

void* spawnEnemy(void* thr);      //Spawn an enemy at coordinates of nextPosition
void driveEnemy(struct enemy * e);      //Manages an enemy movement
void setEnemy(struct enemy * e);        //Sets an enemy
void cleanEnemy(struct enemy * e);      //Disappears an enemy whitout destroying it
void initEnemy(int x, int y);       //Initializes an enemy at coordinates 'x' and 'y'
void drawEnemy(struct enemy * e);
void enemiesInit();
void* enemiesManagment(void* thr);
void destroyEnemy(int x, int y);        //Destoyes the enemy at coordinates 'x' and 'y'.
void generateEnemy(int i);
int isOccupiedByEnemy(int x, int y);
bool canPutEnemy(int x, int y);
void moveEnemy(int enemyId, int direction);
