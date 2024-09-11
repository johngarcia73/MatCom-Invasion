#define shootDelay 250

#pragma once

struct shoot
{
    int shotId;
    int x;
    int y;
    int active;
    int shooterId;
};

extern struct shoot shoots[200];
extern int shootsNumber;


void generateShoot(int shooterId);      // Generates a shot from respectiveenemy's id, from player if -1
void* manageShoot(void * thr);
void drawShoot(struct shoot s);
void addShoot(struct shoot s);
void shootsInit();
void generateBossShoot(int enemyId, int x, int y);