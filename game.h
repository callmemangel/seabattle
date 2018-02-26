#ifndef GAME_H
#define GAME_H

#define SIZE 10

#include <stdbool.h>
#include "structs.h"

void updateField(char** windowField, Cell** field, bool hideShips);

void printText(char** field, char* text);

void clearTextField(char** textField);

void setShipsInf(int* shipsInf);

int getShipId (int* shot, Cell** field);

Cell** storeField (Cell** field, Cell** tmp);

Cell** mallocField(Cell** field);

void updateShipsInf(char** windowField, int* ships);

void initField(char*** dynamicField, char** field);

void initShipsInf(char*** dynamicField, char** shipsInf);

void startGame (Player* player_1, Player* player_2, char gameMode);

void initCells (Cell** field);

void doShot (Player* player_1, Player* player_2, char shotMode, GameWindow window);

int* getShot (char shotMode);

bool isHit (int* shot, Cell** field);

bool isKilled(const int id, Ship* ships);

char* getPlayerName (char* name, char gameMode);

char getGameMode (void);

bool wannaRepeat (void);

bool checkWin (Cell** field);

void packField(Cell** field, char** windowField, char opt);

void setEnvire(Ship ship, Cell** field);

int* getUserShot(void);

void clearBuff(void);

#endif
