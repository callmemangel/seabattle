#ifndef WINDOW_HH 
#define WINDOW_HH

typedef struct {

    int width;
    int height;

    char** field;
    char** color_map;

} Window;


Window createWindow(const int width, const int height);

Window createField(Window window, const int x, const int y, const int width, const int height);

void renderWindow(Window window, int option);

#endif
