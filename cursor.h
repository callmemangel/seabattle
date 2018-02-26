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
    char prev_value;
    char prev_color;

    Buffer drawCoords;

    Window window;

    char sign;    
    char color;

} Cursor;


void renderCursor(const Cursor cursor);

void storePrevCell(Cursor* cursor);

void recoverPrevCell(const Cursor cursor);

void moveCursor(Cursor* cursor, char vector, bool start_draw);

void initCursorOnWindow(Cursor* cursor, const Window window, const char curs_sign, const char curs_color);

void deleteLastSymbol(Cursor cursor);

char listenInput(void);


#endif
