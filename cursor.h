#ifndef CURSOR_H
#define CURSOR_H

#include "structs.h"

void renderCursor(Cursor cursor);

void moveCursor(Cursor* cursor, char vector);

void initCursorOnField(Cursor* cursor, char** field, int field_w, int field_h,  char curs_sign);

char listenInput(void);


#endif
