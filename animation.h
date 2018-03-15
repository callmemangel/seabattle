#ifndef ANIMATION_H
#define ANIMATION_H

#include "cursor.h"
#include "window.h"
#include "structs.h"


#define TICK_RATE 99000

typedef struct {

    int width;
    int height;

    int x;
    int y;
    
    int frames;

    Window stored_area;

    int currFrame;

    int ms;

    char** frame_bodies;
    char** frame_colors;

} Animation;

Animation createSalutAnimation(const int x, const int y, const char color);
Animation createBoomAnimation(int x, int y);
Animation createShipSetSplashAnimation(int x, int y, Ship ship);
Animation createSplashAnimation(int x, int y);

void freeAnimation(Animation* animation);

Window storeArea(Window window, int x, int y, int width, int height);
Window storeNullArea(Window window, int x, int y, int width, int height);
void recoverArea(Window window, Window stored_area, int x, int y, int width, int height);

void renderAnimationOnWindow(Animation animation, Window window, Window root);

void renderAnimationArrayOnWindow(Animation* animations, Window window, int *size, char opt);
void renderFrameOnWindow(Animation animation, int number,  Window window, int x, int y);

void deleteAnimationInArray(Animation** animations, int size,  int position);
int* addAnimation(Animation** animations, Animation animation);

#endif
