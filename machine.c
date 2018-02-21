#include "machine.h"
#include <stdio.h>


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
    "TODO";
}
