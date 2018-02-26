#include "window.h"
#include "cursor.h"
#include "structs.h"
#include "getch.h"
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_H 46 
#define WINDOW_W 90

#define CANVAS_W 90 
#define CANVAS_H 44 


#define TEXTFIELD_W 80
#define TEXTFIELD_H 3


void clear (Window canvas)
{
    for (int i = 0; i < CANVAS_H; i++)
        for (int j = 0; j < CANVAS_W; j++) {
            canvas.field[i][j] = ' ';
            canvas.color_map[i][j] = ' ';
        }
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

void clearCurrCell (Cursor* cursor)
{
    cursor -> prev_value = ' ';
    cursor -> prev_color = ' ';
}


void main(void)

{
    Window root = createWindow(WINDOW_W, WINDOW_H); 
    
    Window textField = createField(root, 0, 0, TEXTFIELD_W, TEXTFIELD_H);
    sprintf(textField.field[0] + 12, "SIMPLE CANVAS");

    Window canvas = createField(root, 0, 1, CANVAS_W, CANVAS_H);

    char sign = '0';
    char color = 'w';
    bool start_draw = false;

    Cursor cursor;
    initCursorOnWindow(&cursor, canvas, sign, color);
    
    renderCursor(cursor);
    renderWindow(root, 0);

    while(1)
    {
        
        char vector = '\0';

        char input = getch();
        
        switch (input) {

            case '\033': 
                vector = getArrowVector();
                break;
            
            case '\n':
                if (start_draw)
                    start_draw = false;
                else
                    start_draw = true;
                break;

            case 'c':
                cursor.color = getch();
                break;

            case '`':
                clear(canvas);
                break;

            case 'r':
                clearCurrCell(&cursor);
                break;

            case 127:
                deleteLastSymbol(cursor);
                break;

            default:
                cursor.sign = input;

        }

        moveCursor(&cursor, vector, start_draw);
        renderWindow(root, 0);
    }

}
