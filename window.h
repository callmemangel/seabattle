#ifndef WINDOW_HEADER
#define WINDOW_HEADER

typedef struct {

    int width;
    int height;

    char** field;
    char** color_map;

} Window;

void freeWindow(Window* window);

Window createWindow(const int width, const int height);
Window createField(Window window, const int x, const int y, const int width, const int height);

void renderWindow(Window window, int option);
char* getColor(char color);

#endif
