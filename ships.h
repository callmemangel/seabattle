#ifndef SHIPS_H
#define SHIPS_H

#include <stdbool.h>

#include "structs.h"
#include "player.h"


void setShips (Player* player);
char getSetMode (Player player);
char getCursorSetMode(Player player);

void setShipsLeft(int* ships_left);
void updateShipsLeft(Window ships_left, int* ships);
bool isEmpty (int* ships_left);
bool contains (Ship ship, int* ships_to_set);

int* getCoords(char set_mode, GameWindow window, int* ships_left);
int* getCursorCoords(GameWindow window, int* ships_left);
int* getFullCoords(int coords[4]);
int chooseShip(GameWindow window, int* ships_left);

bool validCoords(int coords[4], int number);
bool checkCoords (int coords[4], Cell** field);
bool checkSize (int coords[4]);
bool checkEnv (int coords[4], Cell** field);

void initShip (Ship* ship, const int id, int* coords);
void initCells (Cell** field);

void setShip (Ship* ship, int* coords, Cell** field);
void unsetShip (Ship ship);
void deleteShip(Ship ship, int* ships_to_set);
bool isAgreed(void);

bool isHit (int* shot, Cell** field);
bool isKilled(const int id, Ship* ships);
int getShipId (int* shot, Cell** field);

int* createSetArea(Ship ship);
void setEnvire(Ship ship, Cell** field);

int calcSize(int* coords);
int calcDist(int x1, int y1, int x2, int y2);


#endif
