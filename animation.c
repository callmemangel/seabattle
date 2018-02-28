#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "window.h"

#define TICK_RATE 99000

typedef struct {

    int width;
    int height;
    
    int frames;

    int ms;

    char** frame_bodies;
    char** frame_colors;

} Animation;

Window storeArea(Window window, int x, int y, int width, int height)
{
    Window stored_area = createWindow(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            stored_area.field[i][j] = window.field[y + i][x + j];
            stored_area.color_map[i][j] = window.color_map[y + i][x + j]; 
        } 
         
    }
    return stored_area;
}

void recoverArea(Window window, Window stored_area, int x, int y, int width, int height)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            window.field[y + i][x + j] = stored_area.field[i][j];
            window.color_map[y + i][x + j] = stored_area.color_map[i][j];  
        } 
         
    }
}



void renderFrameOnWindow(Animation animation, int number,  Window window, int x, int y)
{
    for (int i = 0; i < animation.height; i++) {
        for (int j = 0; j < animation.width; j++) {
            window.field[y + i][x + j] = animation.frame_bodies[number][i * animation.width + j];
            window.color_map[y + i][x + j] = animation.frame_colors[number][i * animation.width + j];
        }
    }
}

void renderAnimationOnWindow(Animation animation, Window window, int x, int y)
{
    Window stored_area = storeArea(window, x, y, animation.width, animation.height);

    for (int i = 0; i < animation.frames; i++) {
        renderFrameOnWindow(animation, i, window, x, y);
        renderWindow(window, 0);
        usleep(animation.ms);
    }

    recoverArea(window, stored_area, x, y, animation.width, animation.height);
}

Animation createSplashAnimation(void)
{
    Animation splash;

    splash.width = 3;
    splash.height = 3;
    splash.frames = 11;
    splash.ms = TICK_RATE;

    splash.frame_bodies = malloc(sizeof(char*) * splash.frames);
    splash.frame_colors = malloc(sizeof(char*) * splash.frames);

    for (int i = 0; i < splash.frames; i++) {
        splash.frame_bodies[i] = malloc(sizeof(char) * splash.width * splash.height);
        splash.frame_colors[i] = malloc(sizeof(char) * splash.width * splash.height);
    }

    sprintf(splash.frame_bodies[0], "   "
                                    " O "
                                    "   ");      

    sprintf(splash.frame_bodies[1], " . "
                                    ".o."
                                    " . ");      


    sprintf(splash.frame_bodies[2], " o "
                                    "o.o"
                                    " o ");      
    
    sprintf(splash.frame_bodies[3], "OoO"
                                    "o o"
                                    "OoO");      

    sprintf(splash.frame_bodies[4], "OoO"
                                    "o o"
                                    "OoO");      

    sprintf(splash.frame_bodies[5], "o.o"
                                    ". ."
                                    "o.o");      

    sprintf(splash.frame_bodies[6], ". ."
                                    " o "
                                    ". .");      


    sprintf(splash.frame_bodies[7], " o "
                                    "oOo"
                                    " o ");      


    sprintf(splash.frame_bodies[8], " . "
                                    ".o."
                                    " . ");      


    sprintf(splash.frame_bodies[9], "   "
                                    " . "
                                    "   ");      

    sprintf(splash.frame_bodies[10], "   "
                                     "   "
                                     "   ");      


    sprintf(splash.frame_colors[0], "   "
                                    " W "
                                    "   ");      

    sprintf(splash.frame_colors[1], " b "
                                    "bBb"
                                    " b ");      


    sprintf(splash.frame_colors[2], " B "
                                    "BbB"
                                    " B ");      
    
    sprintf(splash.frame_colors[3], "WBW"
                                    "B B"
                                    "WBW");      

    sprintf(splash.frame_colors[4], "WWW"
                                    "W W"
                                    "WWW");      

    sprintf(splash.frame_colors[5], "WWW"
                                    "W W"
                                    "WWW");      

    sprintf(splash.frame_colors[6], "b b"
                                    " B "
                                    "b b");      


    sprintf(splash.frame_colors[7], " B "
                                    "BWB"
                                    " B ");      


    sprintf(splash.frame_colors[8], " b "
                                    "bBb"
                                    " b ");      


    sprintf(splash.frame_colors[9], "   "
                                    " b "
                                    "   ");      


    return splash;

}

void main(void)
{
    Window window = createWindow(10, 10);

    Animation splash = createSplashAnimation();
    while (1) {

        renderAnimationOnWindow(splash, window, 1, 1);
        getchar();
    }



}
