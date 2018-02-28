#include "cursor.h"
#include "stack.h"
#include "getch.h"
#include "window.h"
#include <stdlib.h>
#include <stdio.h>

void renderCursor(Cursor cursor)
{
    for (int i = 0; i < cursor.size; i++) {
        for (int j = 0; j < cursor.size; j++) {

            cursor.window.field[cursor.curr_y + i][cursor.curr_x + j] = cursor.sign;
            cursor.window.color_map[cursor.curr_y + i][cursor.curr_x + j] = cursor.color;
        }
    }
}

void moveCursor(Cursor* cursor, char vector, bool start_draw)
{
    if (!start_draw) {
        recoverPrevCell(*cursor);
    }

    else {
        for (int i = 0; i < cursor -> size; i++) {
            for (int j = 0; j < cursor -> size; j++) {
 
                cursor -> stored_values[i * cursor -> size + j] = cursor -> sign;   
                cursor -> stored_colors[i * cursor -> size + j] = cursor -> color;   
            }    
        }
    }
    
    switch (vector) {
    
    case 'l':
       if (cursor -> curr_x == 0) 
           break;

       cursor -> curr_x-= 1;
       break;
       
    case 'r':
       if (cursor -> curr_x + cursor -> size == cursor -> window.width) 
           break;

       cursor -> curr_x += 1;
       break;

    case 'u':
       if (cursor -> curr_y == 0) 
           break;

       cursor -> curr_y -= 1;
       break;

    case 'd':
       if (cursor -> curr_y + cursor -> size == cursor -> window.height) 
           break;

       cursor -> curr_y += 1;
       break;
   
    }
    
    if (!start_draw)
        storePrevCell(cursor);

    else {
        push(cursor -> drawCoords, cursor -> size);
        push(cursor -> drawCoords, cursor -> curr_x);
        push(cursor -> drawCoords, cursor -> curr_y);
    }

    renderCursor(*cursor);
}

char getArrowVector(void)
{
    getch();

    char vector;

    switch(getch())
    {
    
        case 'A': 
            vector = 'u';
            break;

        case 'B':
            vector = 'd';
            break;

        case 'C':
            vector = 'r';
            break;

        case 'D':
            vector = 'l';
            break;
    
    }

    return vector;

}


void storePrevCell(Cursor* cursor)
{
    cursor -> prev_x = cursor -> curr_x;
    cursor -> prev_y = cursor -> curr_y;

    for (int i = 0; i < cursor -> size; i++) {
        for (int j = 0; j < cursor -> size; j++) {
          cursor -> stored_values[i * cursor -> size + j] = cursor -> window.field[cursor -> curr_y + i][cursor -> curr_x + j];
          cursor -> stored_colors[i * cursor -> size + j] = cursor -> window.color_map[cursor -> curr_y + i][cursor -> curr_x + j];
          
        } 
    }
}

void recoverPrevCell(Cursor cursor)
{
    for (int i = 0; i < cursor.size; i++) {
        for (int j = 0; j < cursor.size; j++) {

            cursor.window.field[cursor.prev_y + i][cursor.prev_x + j] = cursor.stored_values[i * cursor.size + j];
            cursor.window.color_map[cursor.prev_y + i][cursor.prev_x + j] = cursor.stored_colors[i * cursor.size + j];
        } 
    }
}

void deleteLastSymbol(Cursor* cursor)
{
    if (isEmptyBuffer (cursor -> drawCoords))
        return;

    int y = pop(cursor -> drawCoords);
    int x = pop(cursor -> drawCoords);
    int size = pop(cursor -> drawCoords);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) { 
            cursor -> window.field[y + i][x + j] = ' ';
            cursor -> window.color_map[y + i][x + j] = ' ';
        }
    storePrevCell(cursor);
}
    

void initCursorOnWindow(Cursor* cursor, Window window, char curs_sign, char curs_color)
{

   cursor -> prev_x = 0;
   cursor -> prev_y = 0;

   cursor -> curr_x = 0;
   cursor -> curr_y = 0;

   cursor -> window = window;

   cursor -> stored_values = malloc(sizeof(char));
   cursor -> stored_colors = malloc(sizeof(char));

   cursor -> stored_values[0] = window.field[0][0];
   cursor -> stored_colors[0] = window.color_map[0][0];

   cursor -> sign = curs_sign;

   cursor -> drawCoords.size = 30;
   cursor -> drawCoords.buffer = calloc(30, sizeof(int));

   cursor -> color = curs_color;

   cursor -> size = 1;

}

void freeCursor(Cursor cursor)
{
    free(cursor.stored_values);
    free(cursor.stored_colors);
    free(cursor.drawCoords.buffer);
}

char listenInput(void)
{
    return getch(); 
}


