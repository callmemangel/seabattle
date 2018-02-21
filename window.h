#ifndef WINDOW_H 
#define WINDOW_H

char** createWindow(const int width, const int height);

char** createField(char** window, const int x, const int y, const int height, const int width);

void drawWindow(char** window, const int width, const int height, int option);

#endif
