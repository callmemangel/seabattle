#ifndef WINDOW_HH 
#define WINDOW_HH

char** createWindow(const int width, const int height);

char** createField(char** window, const int x, const int y, const int width, const int height);

void renderWindow(char** window, const int width, const int height, int option);

#endif
