#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "player.h"
#include "game.h"
#include "ships.h"
#include "machine.h"



int main(void)
{
    char gameMode;

    Player player_1;
    Player player_2;

    Ship p1Ships[10];
    Ship p2Ships[10]; 
        
    while (true) { 

        gameMode = getGameMode();

        player_1.name = getPlayerName(gameMode);
        player_2.name = getPlayerName(gameMode); 

        initCells (player_1.field);
        initCells (player_2.field);

          
        setShips(player_1.field, p1Ships, gameMode);
        setShips(player_2.field, p2Ships, gameMode);

        startGame(player_1, player_2, gameMode);
            
        if (!wannaRepeat())
            break;

//        resetGame();
    }


}
