#ifndef STRUCTS_H
#define STRUCTS_H


#define NAME_LENGTH 10

#include <stdbool.h>

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

    char** mainWindow;

    char** gameField;
    char** infoField;

    char** dynamicField;
    char** dynamicInf;

    char** textField;

} GameWindow;

typedef struct {

    int curr_x;
    int curr_y;

    int prev_x;
    int prev_y;
    char prev_value;

    char** window;
    int window_w;
    int window_h;

    char sign;    

} Cursor;

#endif
