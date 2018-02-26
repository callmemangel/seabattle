#include "cursor.h"
#include "stack.h"
#include "getch.h"
#include "window.h"
#include <stdlib.h>

void renderCursor(Cursor cursor)
{
    cursor.window.field[cursor.curr_y][cursor.curr_x] = cursor.sign;
    cursor.window.color_map[cursor.curr_y][cursor.curr_x] = cursor.color;
}

void moveCursor(Cursor* cursor, char vector, bool start_draw)
{
    if (!start_draw) {
        recoverPrevCell(*cursor);
    }

    else {
        cursor -> prev_value = cursor -> sign;
        cursor -> prev_color = cursor -> color; 
    }
    
    switch (vector) {
    
    case 'l':
       if (cursor -> curr_x == 0) 
           break;

       cursor -> curr_x-= 1;
       break;
       
    case 'r':
       if (cursor -> curr_x == cursor -> window.width - 1) 
           break;

       cursor -> curr_x += 1;
       break;

    case 'u':
       if (cursor -> curr_y == 0) 
           break;

       cursor -> curr_y -= 1;
       break;

    case 'd':
       if (cursor -> curr_y == cursor -> window.height - 1) 
           break;

       cursor -> curr_y += 1;
       break;
   
    }
    
    if (!start_draw)
        storePrevCell(cursor);

    else {
        push(cursor -> drawCoords, cursor -> curr_x);
        push(cursor -> drawCoords, cursor -> curr_y);
    }

    renderCursor(*cursor);
}

void storePrevCell(Cursor* cursor)
{
    cursor -> prev_x = cursor -> curr_x;
    cursor -> prev_y = cursor -> curr_y;
    cursor -> prev_value = cursor -> window.field[cursor -> curr_y][cursor -> curr_x];
    cursor -> prev_color = cursor -> window.color_map[cursor -> curr_y][cursor -> curr_x];
}

void recoverPrevCell(Cursor cursor)
{
    cursor.window.field[cursor.prev_y][cursor.prev_x] = cursor.prev_value;
    cursor.window.color_map[cursor.prev_y][cursor.prev_x] = cursor.prev_color;
}

void deleteLastSymbol(Cursor cursor)
{
    if (isEmpty (cursor.drawCoords))
        return;

    int y = pop(cursor.drawCoords);
    int x = pop(cursor.drawCoords);

    cursor.window.field[y][x] = ' ';
    cursor.window.color_map[y][x] = ' ';
}
    

void initCursorOnWindow(Cursor* cursor, Window window, char curs_sign, char curs_color)
{

   cursor -> prev_x = 0;
   cursor -> prev_y = 0;

   cursor -> curr_x = 0;
   cursor -> curr_y = 0;

   cursor -> window = window;

   cursor -> prev_value = window.field[0][0];
   cursor -> prev_color = window.color_map[0][0];

   cursor -> sign = curs_sign;

   cursor -> drawCoords.size = 20;
   cursor -> drawCoords.buffer = calloc(20, sizeof(int));

   cursor -> color = curs_color;

}

char listenInput(void)
{
 
    return getch(); 

}


