#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ao/ao.h>
#include<mpg123.h>

#pragma once

extern bool play;       // Plays music

void initAudio();
void* playAudio(void* thr);