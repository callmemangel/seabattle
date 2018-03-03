#ifndef MACHINE_H
#define MACHINE_H

#include "structs.h"

int* getMachineShot(Player player);

int getMachineLvl(void);

int* getEazyShot(void);

int* getMidShot(Player player);

int* getShotForVector(const int* prev_shot, int* curr_shot, char vector);

char switchVector(const char vector);

char calcVector(int* prev_shot, int* curr_shot);

char getRandVector(const int* shot);

int* getHardShot(void);

int* getMachineCoords(void);

void rearrangeCoords(int coords[4]);

void swap(int* a, int* b);

#endif
