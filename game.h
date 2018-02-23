#ifndef GAME_H
#define GAME_H
#define SIZE 10

#include <stdbool.h>

typedef struct {

    int x;
    int y;

    bool isHitted;

    short shipId;

} Cell;

typedef struct {

    char* name;
    int count;
    Cell** field;

} Player;

void updateField(char** windowField, Cell** field);

Cell** storeField (Cell** field, Cell** tmp);

Cell** mallocField(Cell** field);

void updateShipsInf(char** windowField, int* ships);

void initField(char*** dynamicField, char** field);

void initShipsInf(char*** dynamicField, char** shipsInf);

void startGame (Player player_1, Player player_2, char gameMode);

void initCells (Cell** field);

void doShot (Player player_1, Player player_2, char gameMode);

int getShot (int gameMode);

bool isHit (int shot, Cell** field);

char* getPlayerName (char gameMode);

char getGameMode (void);

bool wannaRepeat (void);

bool checkWin (Cell** field);

void packField(Cell** field, char** windowField, char opt);

void drawHitField (Cell** field);

int getUserShot(void);

void clearBuff(void);




#endif
