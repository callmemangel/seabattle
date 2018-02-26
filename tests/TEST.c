#include <stdio.h>
#include <stdlib.h>
#include "ships.h"

void main(void)

{

        
    int coords[4] = {0, 0, 0, 3};

    int *full = getFullCoords(coords);


    printf("%i, %i\n", full[0], full[1]);
    printf("%i, %i\n", full[2], full[3]);
    printf("%i, %i\n", full[4], full[5]);


}
