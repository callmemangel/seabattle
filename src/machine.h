#ifndef MACHINE_H
#define MACHINE_H

#include "player.h"

int getMachineLvl(void);

int* getMachineShot(Player player);
int* getEazyShot(void);
int* getMidShot(Player player);

char getRandVector(const int* shot);
char calcHitVector(int* prev_shot, int* curr_shot);
char switchVector(const char vector);

int* getShotForVector(const int* prev_shot, int* curr_shot, char vector);

int* getMachineCoords(void);

void rearrangeCoords(int coords[4]);

void swap(int* a, int* b);

#endif
