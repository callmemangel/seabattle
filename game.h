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
    Cell field[SIZE][SIZE];

} Player;


void startGame (Player player_1, Player player_2, char gameMode);

void initCells (Cell field[][SIZE]);

void doShot (Player player_1, Player player_2, char gameMode);

int getShot (int gameMode);

bool isHit (int shot, Cell field[][SIZE]);

char* getPlayerName (char gameMode);

char getGameMode (void);

bool wannaRepeat (void);

bool checkWin (Cell field[][SIZE]);

void drawField (Cell field[][SIZE]);

void drawHitField (Cell field[][SIZE]);

int getUserShot(void);

void clearBuff(void);


#endif
