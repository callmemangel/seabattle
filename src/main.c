#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "window.h"
#include "ships.h"
#include "game.h"
#include "machine.h"
#include "player.h"


int main(void)
{
    char gameMode;

    FILE* ptr = fopen("log.txt", "w");
    fclose(ptr);

    Player player_1;
    Player player_2;

    while (true) { 

        gameMode = getCursorGameMode();

        initPlayer(&player_1, 'p');
        initPlayer(&player_2, gameMode);

        startGame(&player_1, &player_2);          
            
        //if (!wannaRepeat())
  //          break;
//        resetGame();
        break;
    }

}
