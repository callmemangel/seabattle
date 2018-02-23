#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "window.h"




#define WINDOW_W 30 
#define WINDOW_H 25 

#define GAME_FIELD_W 11
#define GAME_FIELD_H 11

#define SHIPS_INF_W 14
#define SHIPS_INF_H 8

#define RENDER_OPT 0 

void main (void)
{
    int shipsToSet[] = {4, 3, 2, 1};

    char** window = createWindow(WINDOW_W, WINDOW_H);
    char** field = createField(window, 2, 2, GAME_FIELD_W, GAME_FIELD_H);
    char** shipsInf = createField(window, 15, 2, SHIPS_INF_W, SHIPS_INF_H);

    char** dynamicField;
    char** dynamicShipsInf;

    initField(field, dynamicField);
    initShipsInf(shipsInf, &dynamicShipsInf);


    renderWindow(window, WINDOW_W, WINDOW_H, RENDER_OPT);

    updateShipsInf(shipsToSet, dynamicShipsInf);
    getchar();

    renderWindow(window, WINDOW_W, WINDOW_H, RENDER_OPT);

}
