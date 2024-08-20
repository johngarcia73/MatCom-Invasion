#include<stdbool.h>
#include<pthread.h>
#include<ncurses.h>
#include"map.h"
#include"control.h"

#pragma once

extern int level;
extern bool nextLevel;

void select2();
void mainMenu();
void drawOptions();
void drawPointer();
void erasePointer();
void drawTitle();

void game();
void endGame();