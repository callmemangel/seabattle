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

        
    while (true) { 

        system("clear");

        gameMode = getGameMode();


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

        setShipsInf(player_1.shipsInf);
        setShipsInf(player_2.shipsInf);

        setShips(&player_1, 'p');
        if (gameMode == 'm')
            setShips(&player_2, 'm');
        else
            setShips(&player_2, 'p');


        setShipsInf(player_1.shipsInf);
        setShipsInf(player_2.shipsInf);


        startGame(&player_1, &player_2, gameMode);
            
        if (!wannaRepeat())
            break;
//        resetGame();
    }


}
