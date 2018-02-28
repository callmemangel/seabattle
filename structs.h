#ifndef STRUCTS_H
#define STRUCTS_H


#define NAME_LENGTH 10

#include <stdbool.h>
#include "window.h"

typedef struct {

    int x;
    int y;

    bool is_hitted;

    short ship_id;

} Cell;

typedef struct {

    unsigned short id;
    unsigned short size;

    Cell** cells;

    bool is_killed;

} Ship;


typedef struct {

    char name[NAME_LENGTH];

    int count;

    Cell** field;
    Ship ships[10];

    int ships_left[4];

    bool is_machine;

} Player;

typedef struct {

    Window root;

    Window game_field;
    Window ships_field;

    Window info_field;
    Window ships_left;

    Window text_field;

} GameWindow;


#endif
