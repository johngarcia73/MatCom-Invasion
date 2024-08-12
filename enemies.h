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
#define maxEnemiesNumber 15

struct enemy enemies[10];
int numberOfEnemies = sizeof(enemies)/sizeof(enemies[0]);
struct position enemyPosLv1[16];                                            // Positions around the core that occupies a level 1 enemy.
int enemyPositionsNumber = sizeof(enemyPosLv1)/sizeof(enemyPosLv1[0]);
int numberEnemiesSpawned = 0;
int numberEnemiesDefeated = 0;

bool aliveEnemies[8];

struct position positionsToSpawnLV1[2];
struct position positionsToSpawnLV2[4];
struct position positionsToSpawnLV3[6];
struct position positionsToSpawnLV4[8];

struct position spawnPositions[4];
int spwansNumber = sizeof(spawnPositions)/sizeof(spawnPositions[0]);
int levelSpawnsNumber;

int last = -1;           // Position reference of the last generated enemy.

void* spawnEnemy(void* thr);      //Spawn an enemy at coordinates of nextPosition
void driveEnemy(struct enemy e);      //Manages an enemy movement
void setEnemy(struct enemy e);        //Sets an enemy
void cleanEnemy(struct enemy e);      //Disappears an enemy whitout destroying it
void initEnemy(int x, int y);       //Initializes an enemy at coordinates 'x' and 'y'
void drawEnemy(struct enemy e);
void enemiesInit();
void* enemiesManagment(void* thr);
void destroyEnemy(int x, int y);        //Destoyes the enemy at coordinates 'x' and 'y'.
void generateEnemy(int index);
int isOccupiedByEnemy(int x, int y);
bool canPutEnemy(int x, int y);
void moveEnemy(int enemyId, int direction);
void assignenemyPos();
void enemyLand(struct enemy e);  
void assignSpawnPos();
