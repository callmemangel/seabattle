
#ifndef SHIPS_H
#define SHIPS_H

#include <stdbool.h>
#include "game.h"

typedef struct {

    unsigned short id;
    unsigned short size;

    Cell** cells;

    bool isKilled;

} Ship;


void setShips (Cell field[][SIZE], Ship* ships, char gameMode);

char getSetMode (char gameMode);

bool isEmpty (int* shipsLeft);

int* getCoords(char setMode);

int calcSize(int* coords);

bool contains (Ship ship, int* shipsToSet);

bool isAgreed(void);

void delete (Ship ship, int* shipsToSet);

int* getUserCoords(void);

void initShips (Ship** ships);

bool setShip (Ship ship, int* coords, Cell field[][SIZE]);

int* getFullCoords(int coords[4]);

bool checkCoords (int coords[4]);

#endif
