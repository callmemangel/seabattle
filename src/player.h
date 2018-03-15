#ifndef PLAYER_H
#define PLAYER_H

#include "structs.h"

typedef struct {

    char name[NAME_LENGTH];

    int count;

    Cell** field;
    Ship ships[10];

    int ships_left[4];

    bool is_machine;

} Player;

void initPlayer(Player* player, char mode);
void getPlayerName (Player* player);

#endif
