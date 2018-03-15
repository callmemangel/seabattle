#include "textfield.h"
#include "string.h"


void clearTextField(Window text_field)
{
    for (int i = 0; i < text_field.height; i++)
        for (int j = 0; j < text_field.width; j++)
            text_field.field[i][j] = ' ';

}


void printToTextField(Window text_field, const char* text, char color)
{
    clearTextField(text_field);
    for (int i = 0; i < text_field.height; i++)
        for (int j = 0; j < text_field.width; j++) {

            if (i * text_field.height + j == strlen(text))
                return;
            text_field.field[i][j] = text[i * text_field.height + j];
            text_field.color_map[i][j] = color;
        }

}
