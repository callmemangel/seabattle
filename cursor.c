#include <stdlib.h>
#include <stdio.h>

#include "cursor.h"
#include "getch.h"
#include "window.h"


void renderCursor(Cursor cursor)
{
    for (int i = 0; i < cursor.height; i++) {
        for (int j = 0; j < cursor.width; j++) {
            cursor.window.field[cursor.curr_y + i][cursor.curr_x + j] = cursor.sign;
            cursor.window.color_map[cursor.curr_y + i][cursor.curr_x + j] = cursor.color;
        }
    }
}

void moveCursor(Cursor* cursor, char vector)
{
    recoverStoredArea(*cursor);

    switch (vector) {
    
    case 'l':
       if (cursor -> curr_x == 0) 
           break;

       cursor -> curr_x-= 1;
       break;
       
    case 'r':
       if (cursor -> curr_x + cursor -> width == cursor -> window.width) 
           break;

       cursor -> curr_x += 1;
       break;

    case 'u':
       if (cursor -> curr_y == 0) 
           break;

       cursor -> curr_y -= 1;
       break;

    case 'd':
       if (cursor -> curr_y + cursor -> height == cursor -> window.height) 
           break;

       cursor -> curr_y += 1;
       break;
   
    }
    
    storeBeforeRender(cursor);
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


void storeBeforeRender(Cursor* cursor)
{
    cursor -> prev_x = cursor -> curr_x;
    cursor -> prev_y = cursor -> curr_y;

    for (int i = 0; i < cursor -> height; i++) {
        for (int j = 0; j < cursor -> width; j++) {
          cursor -> stored_values[i * cursor -> width + j] = cursor -> window.field[cursor -> curr_y + i][cursor -> curr_x + j];
          cursor -> stored_colors[i * cursor -> width + j] = cursor -> window.color_map[cursor -> curr_y + i][cursor -> curr_x + j];
        } 
    }
}

void recoverStoredArea(Cursor cursor)
{
    for (int i = 0; i < cursor.height; i++) {
        for (int j = 0; j < cursor.width; j++) {
            cursor.window.field[cursor.prev_y + i][cursor.prev_x + j] = cursor.stored_values[i * cursor.width + j];
            cursor.window.color_map[cursor.prev_y + i][cursor.prev_x + j] = cursor.stored_colors[i * cursor.width + j];
        } 
    }
}

void initCursorOnWindow(Cursor* cursor, Window window, char curs_sign, char curs_color, int width, int height)
{

   cursor -> curr_x = 0;
   cursor -> curr_y = 0;

   cursor -> window = window;

   cursor -> width = width;
   cursor -> height = height;

   cursor -> stored_values = malloc(sizeof(char) * width * height);
   cursor -> stored_colors = malloc(sizeof(char) * width * height);

   storeBeforeRender(cursor);

   cursor -> sign = curs_sign;

   cursor -> color = curs_color;

}

void freeCursor(Cursor cursor)
{
    free(cursor.stored_values);
    free(cursor.stored_colors);
}

char listenInput(void)
{
    return getch(); 
}


