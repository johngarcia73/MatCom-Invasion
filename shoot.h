#define shootDelay 250

struct shoot
{
    int x;
    int y;
    int active;
};

struct shoot shoots[100];
int shootsNumber = sizeof(shoots)/sizeof(shoots[0]);


void generateShoot();       //Generates a shoot in fornt of the player by pressing 'Space'.
void* manageShoot(void * thr);
void drawShoot(struct shoot s);
void addShoot(struct shoot s);
void shootsInit();
