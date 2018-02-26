#include "window.h"
#include "getch.h"
#include "cursor.h"
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_H 23
#define WINDOW_W 40

#define CANVAS_W 40 
#define CANVAS_H 21 


#define TEXTFIELD_W 40
#define TEXTFIELD_H 3


void clear (char** canvas)
{
    for (int i = 0; i < CANVAS_H; i++)
        for (int j = 0; j < CANVAS_W; j++)
            canvas[i][j] = ' ';

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


void main(void)

{
    char** window = createWindow(WINDOW_W,WINDOW_H);
    char** canvas = createField(window, 0, 2, CANVAS_W, CANVAS_H);

    sprintf(canvas[4] + 5, "SOME TEXT");

    Cursor cursor;

    initCursorOnField(&cursor, canvas, CANVAS_W, CANVAS_H, 'O');
    

    renderCursor(cursor);
    renderWindow(window, WINDOW_W, WINDOW_H, 0);

    while(1)
    {
        
        char vector = '\0';

        char input = listenInput();
        
        switch (input) {

            case '\033': 
                vector = getArrowVector();
                break;
            
            default:
                cursor.sign = input;

        }

        moveCursor(&cursor, vector);
        renderWindow(window, WINDOW_W, WINDOW_H, 0);
    }

}
