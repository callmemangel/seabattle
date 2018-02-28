
#ifndef SHIPS_H
#define SHIPS_H

#include <stdbool.h>
#include "structs.h"


void setShips (Player* player);

char getSetMode (Player player);

bool isEmpty (int* ships_left);

void reset (Ship ship);

int* getCoords(char set_mode, int* coords);

int calcSize(int* coords);

int calcDist(int x1, int y1, int x2, int y2);

bool contains (Ship ship, int* ships_to_set);

bool isAgreed(void);

void delete (Ship ship, int* ships_to_set);

int* getUserCoords(void);

void setShip (Ship* ship, int* coords, Cell** field);

int* getFullCoords(int coords[4]);

bool checkCoords (int coords[4], Cell** field);

bool validCoords(int coords[4], int number);

bool checkSize (int coords[4]);

bool checkEnv (int coords[4], Cell** field);

void initShip (Ship* ship, const int id, int* coords);

#endif
