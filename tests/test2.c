#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "game.h"


void main(void)

{

    Player player_1;
    Player player_2;


    initCells(player_1.field);
    initCells(player_2.field);

    setShips(player_1.field, p1Ships, 'p');

 
    char** window = createWindow(50, 50);


    int fieldWid = 11;
    int fieldH = 11;

    char** windowField = createField(window, 10, 10, fieldWid, fieldH);


    
}
