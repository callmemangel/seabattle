#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "animation.h"
#include "window.h"
#include "game.h"
#include "ships.h"


Animation createSalutAnimation(const int x, const int y, const char color)
{

    Animation startup;
    startup.width = 12;
    startup.height = 8;
    startup.frames = 10;
    startup.currFrame = 0;
    startup.ms = 160000;
    
    startup.x = x;
    startup.y = y;

    startup.frame_bodies = malloc(sizeof(char*) * startup.frames);
    startup.frame_colors = malloc(sizeof(char*) * startup.frames);

    for (int i = 0; i < startup.frames; i++) {
        startup.frame_bodies[i] = malloc(sizeof(char) * startup.width * startup.height);
        startup.frame_colors[i] = malloc(sizeof(char) * startup.width * startup.height);

        for (int j = 0; j < startup.height; j++)
            for (int k = 0; k < startup.width; k++)
                startup.frame_colors[i][j * startup.width + k] = color;
    }
    

    sprintf(startup.frame_bodies[0], "            "
                                     "            "
                                     "            "
                                     "     *      "
                                     "            "
                                     "            "
                                     "            "
                                     "            " );

    sprintf(startup.frame_bodies[1], "            "
                                     "       ,    "
                                     "   , o      "
                                     "    o*o     "
                                     "    ,o      "
                                     "       ,    "
                                     "            "
                                     "            " );

    sprintf(startup.frame_bodies[2], "            "
                                     "  * .   o   " 
                                     "   o O*,    " 
                                     "  O,o@O O   " 
                                     "   . 0 ,o   " 
                                     "   O . *    " 
                                     "     O. *   "
                                     "            " ); 
                                                    


    sprintf(startup.frame_bodies[3], "     O  *   " 
                                     "o & . . & . " 
                                     " . * O*, .* " 
                                     "o .@ @O D @ " 
                                     "#.  @ . * o " 
                                     " o O * O .* " 
                                     "    .O  O . " 
                                     "  *         " );

    sprintf(startup.frame_bodies[4], "  *  *  *   " 
                                     "   +. @#* . " 
                                     "* .@ ** ,0* " 
                                     "  *  # ,+   " 
                                     " o .o jO* D " 
                                     "  * +* *  * " 
                                     "*  @ *. *   " 
                                     "  * .  #    " );

    sprintf(startup.frame_bodies[5], "    *  * * *" 
                                     "  * ,+*  *  " 
                                     "* . * @ * * " 
                                     "  * ,*  r* *" 
                                     "  . +  *,   " 
                                     " *  * r * * " 
                                     "  *  *      " 
                                     "            " );

    sprintf(startup.frame_bodies[6], "  *  *   . *" 
                                     "   , .  * . " 
                                     "* . . .  ,* " 
                                     "  *  ,  *   " 
                                     " .  .  .  * " 
                                     "   .,  *  * " 
                                     "*    *  *   " 
                                     "  *         " );


    sprintf(startup.frame_bodies[7], "  .         " 
                                     "        .   " 
                                     "   *    *   " 
                                     "  .     .   " 
                                     "     *    . " 
                                     "  *    .  . " 
                                     "     .  .   " 
                                     "  .         " );

    sprintf(startup.frame_bodies[8], "  .         " 
                                     "     *  .   " 
                                     "            " 
                                     "  .    .    " 
                                     "          . " 
                                     "   *  .  .  " 
                                     "    .       " 
                                     "            " );

    sprintf(startup.frame_bodies[9], "  .         " 
                                     "            " 
                                     "    *   .   " 
                                     "  .         " 
                                     "      ,     " 
                                     "            " 
                                     "    .       "
                                     "            " ); 




 
    return startup;
}

Animation createBoomAnimation(int x, int y)
{
    Animation boom;

    boom.width = 3;
    boom.height = 3;
    boom.frames = 9;
    boom.currFrame = 0;
    boom.ms = 120000;

    boom.x = x;
    boom.y = y;

    boom.frame_bodies = malloc(sizeof(char*) * boom.frames);
    boom.frame_colors = malloc(sizeof(char*) * boom.frames);

    for (int i = 0; i < boom.frames; i++) {
        boom.frame_bodies[i] = malloc(sizeof(char) * boom.width * boom.height);
        boom.frame_colors[i] = malloc(sizeof(char) * boom.width * boom.height);
    }


    sprintf(boom.frame_bodies[0], "   "
                                  " * "
                                  "   ");      

    sprintf(boom.frame_bodies[1], " o."
                                  "DOo"
                                  " 0.");      

    sprintf(boom.frame_bodies[2], ".*o"
                                  "OD*"
                                  " *o");      


    sprintf(boom.frame_bodies[3], "*oO"
                                  "*@O"
                                  ".o ");      

    sprintf(boom.frame_bodies[4], "O@*"
                                  ".o@"
                                  "*O ");      


    sprintf(boom.frame_bodies[5], "* *"
                                  "***"
                                  " **");      

    sprintf(boom.frame_bodies[6], "*  "
                                  "*  "
                                  " **");      

    sprintf(boom.frame_bodies[7], "  *"
                                  "*  "
                                  "  *");      

    sprintf(boom.frame_bodies[8], "   "
                                  "   "
                                  "   ");      

    sprintf(boom.frame_colors[0], "   "
                                  " R "
                                  "   ");      

    sprintf(boom.frame_colors[1], " W."
                                  "WYW"
                                  " W.");      

    sprintf(boom.frame_colors[2], ".YR"
                                  "RYY"
                                  " YR");      


    sprintf(boom.frame_colors[3], "WYR"
                                  "WYY"
                                  ".R ");      

    sprintf(boom.frame_colors[4], "RYW"
                                  "RYR"
                                  "YR ");      


    sprintf(boom.frame_colors[5], "W W"
                                  "WRW"
                                  " WW");      

    sprintf(boom.frame_colors[6], "W  "
                                  "W  "
                                  "  W");      

    sprintf(boom.frame_colors[7], "  W"
                                  "W  "
                                  "  W");      


    return boom;
}

Animation createShipSetSplashAnimation(int x, int y, Ship ship)
{
    Animation splash;

    int* setArea = createSetArea(ship);
    
    splash.width = setArea[2] - setArea[0] + 1;
    splash.height = setArea[3] - setArea[1] + 1;
    
    char orientation;
    if (splash.width >= splash.height)
        orientation = 'h';
    else
        orientation = 'v';

    int size = ship.size;

    splash.frames = 7;
    splash.currFrame = 0;
    splash.ms = 120000;

    splash.x = x;
    splash.y = y; 

    splash.frame_bodies = malloc(sizeof(char*) * splash.frames);
    splash.frame_colors = malloc(sizeof(char*) * splash.frames);

    for (int i = 0; i < splash.frames; i++) {
        splash.frame_bodies[i] = malloc(sizeof(char) * splash.width * splash.height);
        splash.frame_colors[i] = malloc(sizeof(char) * splash.width * splash.height);
    }
    
    switch (size) { 

        case 1:

        sprintf(splash.frame_bodies[0], "   "
                                        " I "
                                        "   ");      

        sprintf(splash.frame_bodies[1], " . "
                                        ".l."
                                        " . ");      


        sprintf(splash.frame_bodies[2], " o "
                                        "oio"
                                        " o ");      
        
        sprintf(splash.frame_bodies[3], "OoO"
                                        "oio"
                                        "OoO");      

        sprintf(splash.frame_bodies[4], "OOO"
                                        "OlO"
                                        "OOO");      

        sprintf(splash.frame_bodies[5], "o.o"
                                        ".I."
                                        "o.o");      

        sprintf(splash.frame_bodies[6], ". ."
                                        " l "
                                        ". .");      

        sprintf(splash.frame_colors[0], "   "
                                        " G "
                                        "   ");      

        sprintf(splash.frame_colors[1], " b "
                                        "bGb"
                                        " b ");      


        sprintf(splash.frame_colors[2], " B "
                                        "BGB"
                                        " B ");      
        
        sprintf(splash.frame_colors[3], "WBW"
                                        "BGB"
                                        "WBW");      

        sprintf(splash.frame_colors[4], "WWW"
                                        "W W"
                                        "WWW");      

        sprintf(splash.frame_colors[5], "WWW"
                                        "W W"
                                        "WWW");      

        sprintf(splash.frame_colors[6], "b b"
                                        " G "
                                        "b b");      
        break;

    case 2:
        if (orientation == 'h') {
            sprintf(splash.frame_bodies[0], "    "
                                            " II "
                                            "    ");      

            sprintf(splash.frame_bodies[1], " .. "
                                            ".ll."
                                            " .. ");      


            sprintf(splash.frame_bodies[2], " oo "
                                            "oiio"
                                            " oo ");      
            
            sprintf(splash.frame_bodies[3], "OooO"
                                            "oiio"
                                            "OooO");      

            sprintf(splash.frame_bodies[4], "OOOO"
                                            "OllO"
                                            "OOOO");      

            sprintf(splash.frame_bodies[5], "o..o"
                                            ".II."
                                            "o..o");      

            sprintf(splash.frame_bodies[6], ".  ."
                                            " ll "
                                            ".  .");      



            sprintf(splash.frame_colors[0], "   "
                                            " GG "
                                            "   ");      

            sprintf(splash.frame_colors[1], " bb "
                                            "bGGb"
                                            " bb ");      


            sprintf(splash.frame_colors[2], " BB "
                                            "BGGB"
                                            " BB ");      
            
            sprintf(splash.frame_colors[3], "WBBW"
                                            "BGGB"
                                            "WBBW");      

            sprintf(splash.frame_colors[4], "WWWW"
                                            "W  W"
                                            "WWWW");      

            sprintf(splash.frame_colors[5], "WWWW"
                                            "W  W"
                                            "WWWW");      

            sprintf(splash.frame_colors[6], "b  b"
                                            " GG "
                                            "b  b");    
        }

        else {

            sprintf(splash.frame_bodies[0], "   "
                                            " I "
                                            " I "
                                            "   ");      

            sprintf(splash.frame_bodies[1], " . "
                                            ".l."
                                            ".l."
                                            " . ");      

            sprintf(splash.frame_bodies[2], " o "
                                            "oio"
                                            "oio"
                                            " o ");      

            sprintf(splash.frame_bodies[3], "OoO"
                                            "oio"
                                            "oio"
                                            "OoO");      


            sprintf(splash.frame_bodies[4], "OOO"
                                            "OlO"
                                            "OlO"
                                            "OOO");      

            sprintf(splash.frame_bodies[5], "o.o"
                                            ".I."
                                            ".I."
                                            "o.o");      

            sprintf(splash.frame_bodies[6], ". ."
                                            " l "
                                            " l "
                                            ". .");      



            sprintf(splash.frame_colors[0], "   "
                                            " G "
                                            " G "
                                            "   ");      

            sprintf(splash.frame_colors[1], " b "
                                            "bGb"
                                            "bGb"
                                            " b ");      


            sprintf(splash.frame_colors[2], " B "
                                            "BGB"
                                            "BGB"
                                            " B ");      
            
            sprintf(splash.frame_colors[3], "WBW"
                                            "BGB"
                                            "BGB"
                                            "WBW");      

            sprintf(splash.frame_colors[4], "WWW"
                                            "W W"
                                            "W W"
                                            "WWW");      

            sprintf(splash.frame_colors[5], "WWW"
                                            "W W"
                                            "W W"
                                            "WWW");      

            sprintf(splash.frame_colors[6], "b b"
                                            " G "
                                            " G "
                                            "b b");    
        }

        break;

    case 3:
        if (orientation == 'v') {
        
            sprintf(splash.frame_bodies[0], "   "
                                            " I "
                                            " I "
                                            " I "
                                            "   ");      

            sprintf(splash.frame_bodies[1], " . "
                                            ".l."
                                            ".l."
                                            ".l."
                                            " . ");      

            sprintf(splash.frame_bodies[2], " o "
                                            "oio"
                                            "oio"
                                            "oio"
                                            " o ");      

            sprintf(splash.frame_bodies[3], "OoO"
                                            "oio"
                                            "oio"
                                            "oio"
                                            "OoO");      


            sprintf(splash.frame_bodies[4], "OOO"
                                            "OlO"
                                            "OlO"
                                            "OlO"
                                            "OOO");      

            sprintf(splash.frame_bodies[5], "o.o"
                                            ".I."
                                            ".I."
                                            ".I."
                                            "o.o");      

            sprintf(splash.frame_bodies[6], ". ."
                                            " l "
                                            " l "
                                            " l "
                                            ". .");      


            sprintf(splash.frame_colors[0], "   "
                                            " G "
                                            " G "
                                            " G "
                                            "   ");      

            sprintf(splash.frame_colors[1], " b "
                                            "bGb"
                                            "bGb"
                                            "bGb"
                                            " b ");      


            sprintf(splash.frame_colors[2], " B "
                                            "BGB"
                                            "BGB"
                                            "BGB"
                                            " B ");      
            
            sprintf(splash.frame_colors[3], "WBW"
                                            "BGB"
                                            "BGB"
                                            "BGB"
                                            "WBW");      

            sprintf(splash.frame_colors[4], "WWW"
                                            "W W"
                                            "W W"
                                            "W W"
                                            "WWW");      

            sprintf(splash.frame_colors[5], "WWW"
                                            "W W"
                                            "W W"
                                            "W W"
                                            "WWW");      

            sprintf(splash.frame_colors[6], "b b"
                                            " G "
                                            " G "
                                            " G "
                                            "b b");    
        
        }

        else {

            sprintf(splash.frame_bodies[0], "     "
                                            " III "
                                            "     ");      

            sprintf(splash.frame_bodies[1], " ... "
                                            ".lll."
                                            " ... ");      


            sprintf(splash.frame_bodies[2], " ooo "
                                            "oiiio"
                                            " ooo ");      
            
            sprintf(splash.frame_bodies[3], "OoooO"
                                            "oiiio"
                                            "OoooO");      

            sprintf(splash.frame_bodies[4], "OOOOO"
                                            "OlllO"
                                            "OOOOO");      

            sprintf(splash.frame_bodies[5], "o...o"
                                            ".III."
                                            "o...o");      

            sprintf(splash.frame_bodies[6], ".   ."
                                            " lll "
                                            ".   .");      


            sprintf(splash.frame_colors[0], "     "
                                            " GGG "
                                            "     ");      

            sprintf(splash.frame_colors[1], " bbb "
                                            "bGGGb"
                                            " bbb ");      


            sprintf(splash.frame_colors[2], " BBB "
                                            "BGGGB"
                                            " BBB ");      
            
            sprintf(splash.frame_colors[3], "WBBBW"
                                            "BGGGB"
                                            "WBBBW");      

            sprintf(splash.frame_colors[4], "WWWWW"
                                            "W   W"
                                            "WWWWW");      

            sprintf(splash.frame_colors[5], "WWWWW"
                                            "W   W"
                                            "WWWWW");      

            sprintf(splash.frame_colors[6], "b   b"
                                            " GGG"
                                            "b   b");    
        }
        break;

    case 4:
        if (orientation == 'h') {
        
            sprintf(splash.frame_bodies[0], "      "
                                            " IIII "
                                            "      ");      

            sprintf(splash.frame_bodies[1], " .... "
                                            ".llll."
                                            " .... ");      


            sprintf(splash.frame_bodies[2], " oooo "
                                            "oiiiio"
                                            " oooo ");      
            
            sprintf(splash.frame_bodies[3], "OooooO"
                                            "oiiiio"
                                            "OooooO");      

            sprintf(splash.frame_bodies[4], "OOOOOO"
                                            "OllllO"
                                            "OOOOOO");      

            sprintf(splash.frame_bodies[5], "o....o"
                                            ".IIII."
                                            "o....o");      

            sprintf(splash.frame_bodies[6], ".    ."
                                            " llll "
                                            ".    .");      


            sprintf(splash.frame_colors[0], "      "
                                            " GGGG "
                                            "      ");      

            sprintf(splash.frame_colors[1], " bbbb "
                                            "bGGGGb"
                                            " bbbb ");      


            sprintf(splash.frame_colors[2], " BBBB "
                                            "BGGGGB"
                                            " BBBB ");      
            
            sprintf(splash.frame_colors[3], "WBBBBW"
                                            "BGGGGB"
                                            "WBBBBW");      

            sprintf(splash.frame_colors[4], "WWWWWW"
                                            "W    W"
                                            "WWWWWW");      

            sprintf(splash.frame_colors[5], "WWWWWW"
                                            "W    W"
                                            "WWWWWW");      

            sprintf(splash.frame_colors[6], "b    b"
                                            " GGGG"
                                            "b    b");   
        }

        else {
            sprintf(splash.frame_bodies[0], "   "
                                            " I "
                                            " I "
                                            " I "
                                            " I "
                                            "   ");      

            sprintf(splash.frame_bodies[1], " . "
                                            ".l."
                                            ".l."
                                            ".l."
                                            ".l."
                                            " . ");      

            sprintf(splash.frame_bodies[2], " o "
                                            "oio"
                                            "oio"
                                            "oio"
                                            "oio"
                                            " o ");      

            sprintf(splash.frame_bodies[3], "OoO"
                                            "oio"
                                            "oio"
                                            "oio"
                                            "oio"
                                            "OoO");      


            sprintf(splash.frame_bodies[4], "OOO"
                                            "OlO"
                                            "OlO"
                                            "OlO"
                                            "OlO"
                                            "OOO");      

            sprintf(splash.frame_bodies[5], "o.o"
                                            ".I."
                                            ".I."
                                            ".I."
                                            ".I."
                                            "o.o");      

            sprintf(splash.frame_bodies[6], ". ."
                                            " l "
                                            " l "
                                            " l "
                                            " l "
                                            ". .");      




            sprintf(splash.frame_colors[0], "   "
                                            " G "
                                            " G "
                                            " G "
                                            " G "
                                            "   ");      

            sprintf(splash.frame_colors[1], " b "
                                            "bGb"
                                            "bGb"
                                            "bGb"
                                            "bGb"
                                            " b ");      


            sprintf(splash.frame_colors[2], " B "
                                            "BGB"
                                            "BGB"
                                            "BGB"
                                            "BGB"
                                            " B ");      
            
            sprintf(splash.frame_colors[3], "WBW"
                                            "BGB"
                                            "BGB"
                                            "BGB"
                                            "BGB"
                                            "WBW");      

            sprintf(splash.frame_colors[4], "WWW"
                                            "W W"
                                            "W W"
                                            "W W"
                                            "W W"
                                            "WWW");      

            sprintf(splash.frame_colors[5], "WWW"
                                            "W W"
                                            "W W"
                                            "W W"
                                            "W W"
                                            "WWW");      

            sprintf(splash.frame_colors[6], "b b"
                                            " G "
                                            " G "
                                            " G "
                                            " G "
                                            "b b");    
        
        
        }
        break;
    }

    return splash;

}

Animation createSplashAnimation(int x, int y)
{
    Animation splash;

    splash.width = 3;
    splash.height = 3;
    splash.frames = 10;
    splash.currFrame = 0;
    splash.ms = 99000;

    splash.x = x;
    splash.y = y; 

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


void freeAnimation(Animation* animation)
{
    for (int i = 0; i < animation -> frames; i++) {
        free(animation -> frame_bodies[i]); 
        free(animation -> frame_colors[i]); 
    }

    free(animation -> frame_bodies);
    free(animation -> frame_colors);

}


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

Window storeNullArea(Window window, int x, int y, int width, int height)
{
    Window stored_area = createWindow(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            stored_area.field[i][j] = ' ';
            stored_area.color_map[i][j] = ' '; 
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


void renderAnimationOnWindow(Animation animation, Window window, Window root)
{
    Window stored_area = storeArea(window, animation.x, animation.y, animation.width, animation.height);
    renderWindow(stored_area, 1);

    for (int i = 0; i < animation.frames; i++) {
        renderFrameOnWindow(animation, i, window, animation.x, animation.y);
        renderWindow(root, 0);
        usleep(animation.ms);
    }

    recoverArea(window, stored_area, animation.x, animation.y, animation.width, animation.height);
}

void renderAnimationArrayOnWindow(Animation* animations, Window window, int *size, char opt)
{
    for (int i = 0; i < *size; i++) {
        if (animations[i].currFrame == 0) {
            if (opt == 'c')
             animations[i].stored_area = storeNullArea(window, animations[i].x, animations[i].y, 
                                                            animations[i].width, animations[i].height);
            else
             animations[i].stored_area = storeArea(window, animations[i].x, animations[i].y, 
                                                            animations[i].width, animations[i].height);
 
        }
    }

    for (int i = 0; i < *size; i++) {
        if (animations[i].currFrame >= animations[i].frames) {

            recoverArea(window, animations[i].stored_area, animations[i].x, animations[i].y, 
                                                           animations[i].width, animations[i].height); 

            deleteAnimationInArray(&animations, *size, i);

            *size -= 1;
            i--;

            continue;
       }

        renderFrameOnWindow(animations[i], animations[i].currFrame, window, animations[i].x, animations[i].y);
        animations[i].currFrame++;
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


void deleteAnimationInArray(Animation** animations, int size,  int position)
{

    freeAnimation(animations[position]);

    for (int i = position; i < size; i++)  {
    
        *(*animations + i) = *(*animations + i + 1); 
    }

    Animation* animations_tmp = *animations;

    *animations = realloc(*animations, sizeof(Animation) * size);

}

int* addAnimation(Animation** animations, Animation animation)
{
    static int size = 0;
    
    *animations = realloc(*animations, sizeof(Animation) * (size + 1));

    *(*animations + size) = animation;

    size++;

    return &size;
}
