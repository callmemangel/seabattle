#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "player.h"
#include "structs.h"

#define SHIPS_FIELD_SIZE 10

void startGame (Player* player_1, Player* player_2);

void initGameField(GameWindow* window);
void freeGameField(GameWindow field);

Window initMapField(Window game_field);
Window initInfoField(Window info_field);

void doShot (Player* player_1, Player* player_2, GameWindow window);
void updateShipsField(Window ships_field, Cell** field, bool hide_ships);
void updateShipsLeft(Window ships_left, int* ships);

int* getShotAtPlayer(Player player, GameWindow window, char shotMode);
int* getCursorShot(GameWindow window);

bool isWin (Ship* ships);
void renderWinnerWindow(Player player, Window window);

Cell** storeField (Cell** field, Cell** tmp);
Cell** mallocField(Cell** field);
void freeField(Cell** field);

bool wannaRepeat (void);

char getCursorGameMode(void);

void clearInputBuff(void);

#endif
