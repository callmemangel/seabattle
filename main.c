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

        gameMode = getCursorGameMode();
        if (gameMode == 'm')
            player_2.is_machine = true;

        system("clear");

        getPlayerName(&player_1);
        getPlayerName(&player_2); 

        renderWinnerWindow(*player_1, window.root);
        initCells (player_1.field);
        initCells (player_2.field);

        setShips(&player_1);
        setShips(&player_2);

        printf("Player ships setted\n");

        setShipsLeft(player_1.ships_left);
        setShipsLeft(player_2.ships_left);



        startGame(&player_1, &player_2);          
            
        //if (!wannaRepeat())
  //          break;
//        resetGame();
    }


}
