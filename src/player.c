#include "player.h"
#include "game.h"
#include "ships.h"
#include "structs.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void initPlayer(Player* player, char mode) {

    player->field = mallocField(player->field);

    if (mode == 'm')
        player->is_machine = true;
    else
        player->is_machine = false;

    getPlayerName(player);

    initCells(player->field);

    setShips(player);

    setShipsLeft(player->ships_left);

}

void getPlayerName(Player* player)
{
    static int count = 0;

    system("clear");

    if (player->is_machine) {
        strcpy(player->name, "Jasper");
        system("clear");
        return;
    }

    if (count == 0) {
        printf("\n\n\n\n\n\n\n\n\n\n\033[2m                        Player name #1: ");
    }
    else {
        printf("\n\n\n\n\n\n\n\n\n\n\033[2m                        Player name #2: ");
    }

    fgets(player -> name, NAME_LENGTH, stdin);

    player -> name[strlen(player -> name) - 1] = '\0';

    printf("\033[0m");
    system("clear");

    count++;

}

