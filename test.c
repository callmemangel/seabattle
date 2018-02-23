#include <stdio.h>
#include <math.h>
#include "ships.h"
#include "game.h"
#include <stdlib.h>
#include <string.h>


void main(void)
      
{

    Player player_1;
    Player player_2;

    player_1.field = mallocField(player_1.field);    
    player_2.field = mallocField(player_2.field);    

    Ship p1Ships[10];

    for (int i = 0; i < 10; i++)
        p1Ships[i].id = i;

    Ship p2Ships[10];
    for (int i = 0; i < 10; i++)
        p2Ships[i].id = i;

    initCells(player_1.field);
    initCells(player_2.field);

    setShips(player_1.field, p1Ships, 'p');



    int coords[] = {2, 3, 5, 3};
    int coords2[] = {0, 0, 0, 3};
    int coords3[4];

//    memcpy(coords3, getUserCoords(), 'p');
    


}
