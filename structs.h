#ifndef STRUCTS_H
#define STRUCTS_H


#define NAME_LENGTH 10

#include <stdbool.h>
#include "window.h"

typedef struct {

    int x;
    int y;

    bool isHitted;

    short shipId;

} Cell;

typedef struct {

    unsigned short id;
    unsigned short size;

    Cell** cells;

    bool isKilled;

} Ship;


typedef struct {

    char name[NAME_LENGTH];
    int count;
    Cell** field;
    Ship ships[10];
    int shipsInf[4];

} Player;

typedef struct {

    Window mainWindow;

    char** gameField;
    char** infoField;

    char** dynamicField;
    char** dynamicInf;

    char** textField;

} GameWindow;



#endif
