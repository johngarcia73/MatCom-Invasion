#include<pthread.h>
#include<stdbool.h>

#pragma once

extern pthread_t threads[100];
extern bool usingThread[100];
extern int threadPointer;
extern bool restart;

void killAll();