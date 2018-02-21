#include <stdio.h>
#include <stdlib.h>
#include "window.h"



char** createWindow(const int width, const int height)
{
    static char** window;

    window = calloc(height, sizeof(char*));

    for (int i = 0; i < height; i++)
        window[i] = calloc(width, sizeof(char));

    return window;
}

char** createField(char** window, const int x, const int y, const int width, const int height)
{

    static char** field;

    field = malloc(sizeof(char*) * height);

    for (int i = 0; i < height; i++)
            field[i] = *(window + y + i) + x;

    return field;

}


void drawWindow (char** window, const int width, const int height, int option)
{
    char sign = ' ';

    if (option == 1)
        sign = '.';

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            if (window[i][j] == 0)
               printf("%2c", sign);
            else
               printf("%2c", window[i][j]); 

        printf("\n");
    }

}
