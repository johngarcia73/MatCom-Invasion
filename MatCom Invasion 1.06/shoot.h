#define shootDelay 250

#pragma once

struct shoot
{
    int x;
    int y;
    int active;
};

extern struct shoot shoots[100];
extern int shootsNumber;


void generateShoot();       //Generates a shoot in fornt of the player by pressing 'Space'.
void* manageShoot(void * thr);
void drawShoot(struct shoot s);
void addShoot(struct shoot s);
void shootsInit();
