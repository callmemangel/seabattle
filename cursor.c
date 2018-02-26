#include "cursor.h"
#include "structs.h"
#include "getch.h"
#include "window.h"


void renderCursor(Cursor cursor)
{
    cursor.window[cursor.curr_y][cursor.curr_x] = cursor.sign;
}

void moveCursor(Cursor* cursor, char vector)
{
    
    cursor -> window[cursor -> prev_y][cursor -> prev_x] = cursor -> prev_value;

    switch (vector) {
    
    case 'l':
       if (cursor -> curr_x == 0) 
           break;

       cursor -> curr_x-= 1;
       break;
       
    case 'r':
       if (cursor -> curr_x == cursor -> window_w - 1) 
           break;

       cursor -> curr_x += 1;
       break;

    case 'u':
       if (cursor -> curr_y == 0) 
           break;

       cursor -> curr_y -= 1;
       break;

    case 'd':
       if (cursor -> curr_y == cursor -> window_h - 1) 
           break;

       cursor -> curr_y += 1;
       break;
    
    }

    cursor -> prev_x = cursor -> curr_x;
    cursor -> prev_y = cursor -> curr_y;
    cursor -> prev_value = cursor -> window[cursor -> curr_y][cursor -> curr_x];

    renderCursor(*cursor);
}
    

void initCursorOnField(Cursor* cursor, char** field, int field_w, int field_h,  char curs_sign)
{
   cursor -> prev_x = 0;
   cursor -> prev_y = 0;

   cursor -> curr_x = 0;
   cursor -> curr_y = 0;

   cursor -> window = field;
   cursor -> window_w = field_w;
   cursor -> window_h = field_h;

   cursor -> prev_value = field[0][0];

   cursor -> sign = curs_sign;

}

char listenInput(void)
{
 
    return getch(); 

}


