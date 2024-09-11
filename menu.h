#include<stdbool.h>
#include<pthread.h>
#include<ncurses.h>
#include<string.h>
#include"map.h"
#include"control.h"
#include"audio.h"

#pragma once


void select2();
void mainMenu();
void drawOptions();
void drawPointer();
void erasePointer();
void drawTitle();
void draw_text(int start_y, int start_x, const char *text);
void draw_rectangle(int y, int x, int height, int width);

void game();
void endGame();
void winnerScreen();