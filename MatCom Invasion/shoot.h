struct shoot
{
    int ascii;
    int x;
    int y;
};

void generateShoot();       //Generates a shoot in fornt of the player by pressing 'Space'.
void* shootThread(void* thr);       //Creates a thread to manage an individual shoot.
void manageShoot(struct shoot s);       //Manages a shoot trayectory.
void drawShoot(struct shoot s);