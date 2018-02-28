#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>
#include "window.h"
#include "stack.h"

typedef struct {

    int curr_x;
    int curr_y;

    int prev_x;
    int prev_y;

    char* stored_values;
    char* stored_colors;

    Buffer drawCoords;

    Window window;

    char sign;    
    char color;

    int size;

} Cursor;


void freeCursor(Cursor cursor);

char getArrowVector(void);

void renderCursor(const Cursor cursor);

void storePrevCell(Cursor* cursor);

void recoverPrevCell(const Cursor cursor);

void moveCursor(Cursor* cursor, char vector, bool start_draw);

void initCursorOnWindow(Cursor* cursor, const Window window, const char curs_sign, const char curs_color);

void deleteLastSymbol(Cursor* cursor);

char listenInput(void);


#endif
