#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include "ships.h"



int getMachineShot()
{
    static int machineLvl = -1;

    if (machineLvl == -1)
        machineLvl = getMachineLvl();

    int shot;

    if (machineLvl == 1)
        shot = getEazyShot();
    else if (machineLvl == 2) 
        shot = getMidShot();
    else
        shot = getHardShot();

    return shot;
}

int getMachineLvl(void)
{
    int lvl;

    printf("Choose lvl of hardness\n"
            "0 - eazy"
            "1 - middle"
            "2 - hard\n");

    do {

        scanf("%i", lvl);

    } while (lvl != 0 && lvl != 1 && lvl != 2);

    return lvl;

}

int getEazyShot()
{



    return 0;
}


int getMidShot()
{




    return 0;
}

int getHardShot()
{




    return 0;
}

int* getMachineCoords(void)
{
    static int coords[4];

    int sizes[8] = {-3, -2, -1, 0, 0, 1, 2, 3};

    coords[0] = rand() % 10; //3 x
    coords[1] = rand() % 10; //7 y
    
    do {

        int size = sizes[rand() % 8]; 
        
        int randNum = rand() % 2;

        coords[randNum + 2] = coords[randNum] + size;

        coords[(randNum + 1) % 2 + 2] = coords[(randNum + 1) % 2];

   
    } while(!validCoords(coords));

 
    rearrangeCoords(coords);

    return coords;

}

void rearrangeCoords(int coords[4])
{
    if (coords[0] == coords[2])
    {
        if (coords[1] > coords[3])
        {
            swap(&coords[1], &coords[3]);
        } 
    
    }

    if (coords[1] == coords[3])
        if (coords[0] > coords[2])
            swap(&coords[0], &coords[2]);

}


void swap(int *a, int* b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;

}
