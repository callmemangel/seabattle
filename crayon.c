#include "window.h"
#include "getch.h"
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_H 23
#define WINDOW_W 80

#define CANVAS_W 80 
#define CANVAS_H 21 


#define TEXTFIELD_W 40
#define TEXTFIELD_H 3

typedef struct {

   int currX;
   int currY;
   char sign;

} Cursor;

typedef struct {
    int x;
    int y;
    char value;

} StoredValue;


void renderCursor(char** window, char** canvas, Cursor cursor)
{
    int x = cursor.currX;
    int y = cursor.currY;

    canvas[y][x] = cursor.sign;

    renderWindow(window, WINDOW_W, WINDOW_H, 0);

}

void moveCursor(char** window, Cursor* cursor, char vector, char** canvas, bool draw)
{
    static StoredValue stored;
    static int moves = 0;
    
    if (moves == 0) {
        stored.x = 0;
        stored.y = 0;
        stored.value = canvas[0][0]; 
    }

    switch (vector) {
    
    case 'l':
       if (cursor -> currX == 0) 
           break;

       cursor -> currX -= 1;
       break;
       
    case 'r':
       if (cursor -> currX == CANVAS_W - 1) 
           break;

       cursor -> currX += 1;
       break;

    case 'u':
       if (cursor -> currY == 0) 
           break;

       cursor -> currY -= 1;
       break;

    case 'd':
       if (cursor -> currY == CANVAS_H - 1) 
           break;

       cursor -> currY += 1;
       break;
    
    }

    canvas[stored.y][stored.x] = stored.value;

    if (draw) {
        stored.value = cursor -> sign;
    }

    stored.x = cursor -> currX;
    stored.y = cursor -> currY;
    
    if (!draw) {
       stored.value = canvas[cursor -> currY][cursor -> currX]; 
    }

    renderCursor(window, canvas,  *cursor);
    moves++;

}


void initCursor (Cursor* cursor)
{
    cursor -> currX = 0;
    cursor -> currY = 0;
    cursor -> sign = '0';
}

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

void clearSymb (char** canvas, Cursor cursor)
{
    canvas[cursor.currY][cursor.currX] = ' ';
}


void main(void)

{
    char** window = createWindow(WINDOW_W,WINDOW_H);
    char** textField = createField(window, 13, 0, TEXTFIELD_W, TEXTFIELD_H);
    char** canvas = createField(window, 0, 2, CANVAS_W, CANVAS_H);

    sprintf(textField[0], "SIMPLE CANVAS");

    Cursor cursor;

    bool isDraw = false;

    initCursor(&cursor);
    
    moveCursor(window, &cursor, '0', canvas, isDraw);

    while(1)
    {
        
        char vector = '\0';

        char input = getch();
        
        switch (input) {

            case '\033': 
                vector = getArrowVector();
                break;
            
            case '\n':
                if (isDraw)
                    isDraw = false;
                else
                    isDraw = true;
                break;


            case '`':
                clear(canvas);
                break;

            case 127:
                cursor.sign = ' ';
                moveCursor(window, &cursor, 'O', canvas, true);
                cursor.sign = ' ';
                break;

            default:
                cursor.sign = input;

        }

        moveCursor(window, &cursor, vector, canvas, isDraw);
    }

}
