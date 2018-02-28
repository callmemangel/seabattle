#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "window.h"



Window createWindow(const int width, const int height)
{
    Window window;

    window.field = calloc(height, sizeof(char*));
    window.color_map = calloc(height, sizeof(char*));

    window.width = width;
    window.height = height;

    for (int i = 0; i < height; i++) {
        window.field[i] = calloc(width, sizeof(char));
        window.color_map[i] = calloc(width, sizeof(char));
    }

    return window;
}

Window createField(Window window, const int x, const int y, const int width, const int height)
{

    Window field;

    field.field = calloc(height, sizeof(char*));
    field.color_map = calloc(height, sizeof(char*));

    field.width = width;
    field.height = height;

    for (int i = 0; i < height; i++) {
            field.field[i] = *(window.field + y + i) + x;
            field.color_map[i] = *(window.color_map + y + i) + x;
    }

    return field;

}

char* getColor(char color)
{
    static char* ansi_color;

    ansi_color = malloc(sizeof(char) * 6);
    int bold;

    if (isupper(color) != 0) {
        bold = 3; 
    }
    else {
        bold = 2;
        color = toupper(color); 
    }
        

    int color_num;

    switch (color) {
        case 'R':
            color_num = 31;
            break;
        case 'G':
            color_num = 32;
            break;
        case 'Y':
            color_num = 33;
            break;
        case 'B':
            color_num = 34;
            break;
        case 'P':
            color_num = 35;
            break;
        case 'C':
            color_num = 36;
            break;
        default:
            color_num = 37;
            break;
    }
     
    sprintf(ansi_color, "\033[%i;%im", color_num, bold);

    return ansi_color;

}


void renderWindow (Window window, int option)
{

    system("clear");
    char sign = ' ';

    if (option == 1)
        sign = '.';

    char* ansi_color;

    for (int i = 0; i < window.height; i++)
    {
        for (int j = 0; j < window.width; j++) {
 
            ansi_color = getColor(window.color_map[i][j]);

            if (window.field[i][j] == 0 || window.field[i][j] == ' ')
               printf("%2c", sign);
            else
               printf("%s%2c\033[0m", ansi_color, window.field[i][j]); 

            free(ansi_color);
        }

        printf("\n");
    }

}

