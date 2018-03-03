#ifndef GAME_H
#define GAME_H

#define SIZE 10

#include <stdbool.h>
#include "structs.h"

void initGameField(GameWindow* window);

int* createSetArea(Ship ship);

void updateShipsField(Window ships_field, Cell** field, bool hide_ships);

void clearTextField(Window text_field);

void printToTextField(Window text_field, const char* text, char color);

void setShipsLeft(int* ships_left);

int getShipId (int* shot, Cell** field);

Cell** storeField (Cell** field, Cell** tmp);

Cell** mallocField(Cell** field);

void updateShipsLeft(Window ships_left, int* ships);

Window initMapField(Window game_field);

Window initInfoField(Window info_field);

void startGame (Player* player_1, Player* player_2);

void initCells (Cell** field);

char getCursorShipSet(Player player);

void doShot (Player* player_1, Player* player_2, GameWindow window);

int* getShotAtPlayer(Player player, GameWindow window, char shotMode);

bool isHit (int* shot, Cell** field);

bool isKilled(const int id, Ship* ships);

void getPlayerName (Player* player);

char getGameMode (void);

char getCursorGameMode(void);

bool wannaRepeat (void);

bool isWin (Ship* ships);

//void packField(Cell** field, char** windowField, char opt);

void setEnvire(Ship ship, Cell** field);

int* getUserShot(void);

int* getCursorShot(GameWindow window);

void renderWinnerWindow(Player player, Window window);

void clearBuff(void);

#endif
