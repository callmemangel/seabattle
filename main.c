#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "window.h"
#include "ships.h"
#include "game.h"
#include "machine.h"

//TODO create menu 

int main(void)
{
    char gameMode;

    Player player_1;
    Player player_2;


    player_1.field = mallocField(player_1.field);    
    player_2.field = mallocField(player_2.field);    

    player_1.is_machine = false;
    player_2.is_machine = false;

        
    while (true) { 

        system("clear");

        gameMode = getGameMode();
        if (gameMode == 'm')
            player_2.is_machine = true;

        system("clear");

        printf("Player1 name: ");
        getPlayerName(player_1.name, 'p');

        if (gameMode == 'p') {
            printf("Player2 name: ");
            getPlayerName(player_2.name, 'p'); 
        }
        else
            getPlayerName(player_2.name, 'a');


        initCells (player_1.field);
        initCells (player_2.field);

        printf("CELLS INITED\n");

        setShipsLeft(player_1.ships_left);
        setShipsLeft(player_2.ships_left);

        printf("ships setted\n");

        setShips(&player_1);
        setShips(&player_2);


        setShipsLeft(player_1.ships_left);
        setShipsLeft(player_2.ships_left);


        startGame(&player_1, &player_2);
            
        if (!wannaRepeat())
            break;
//        resetGame();
    }


}
