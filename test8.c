#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>



bool validCoords(int coords[4])
{
    
   if (coords[0] > 'j' || coords[0] < 0 || coords[2] > 'j' || coords[2] < 0 ||
       coords[1] > 9   || coords[1] < 0 || coords[3] > 9   || coords[3] < 0 )
   {
            return false;
   }

   return true;
}


void getMachineCoords(void)
{
    static int coords[4];
    srand(time(NULL));

    int tmp[8];

    coords[0] = rand() % 10; //3 x
    printf("COORD 0 = %i\n", coords[0]);
    coords[1] = rand() % 10; //7 y
    printf("COORD 1 = %i\n", coords[1]);
    
    
    do {
        int size = rand() % 7 - 4 + 1 ; 
        
        int randNum = rand() % 2;

        coords[randNum + 2] = coords[randNum] + size;
        

        coords[(randNum + 1) % 2 + 2] = coords[(randNum + 1) % 2];

        printf("COORD 2 = %i\n", coords[2]);

        printf("COORD 3 = %i\n", coords[3]);

        
        printf("SIZE = %i\n", size);
        getchar();
    
    } while(!validCoords(coords));


}

void main(void)

{
    getMachineCoords();
}

