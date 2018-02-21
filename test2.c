#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "game.h"


void attachField(Cell field[][SIZE], char** windowField)
{
    char** buff = windowField;
    const char letters[] = "ABCDEFGHIJ";

    char* buf = *windowField;

    sprintf(buf, "%c", ' ');
    buf++;

    for (int i = 0; i < 10; i++) {
        sprintf(buf, "%c", letters[i]);
        buf++;
    }

    
    buf = *(++buff);

    for (int i = 0; i < 10; i++) {
        
        sprintf(buf, "%i", i);
        buf++;

        for (int j = 0; j < 10; j++)

            if (field[i][j].shipId != -1) {

                sprintf(buf, "%c", 'I');
                buf++;
            }

            else {
                sprintf(buf, "%c", '~');
                buf++;
            }
        buf = *(++buff);
    }
}


void main(void)

{

    Player player_1;
    Player player_2;


    initCells(player_1.field);
    initCells(player_2.field);

//    setShips(player_1.field, p1Ships, 'p');

 
    char** window = createWindow(50, 50);


    int fieldWid = 11;
    int fieldH = 11;

    char** windowField = createField(window, 10, 10, fieldWid, fieldH);

    attachField(player_1.field, windowField);

    
    drawWindow(window, 50, 50, 0);
}
