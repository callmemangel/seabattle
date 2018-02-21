#include <stdio.h>
#include <stdlib.h>





void main(void)
{

    int** array;
    array = malloc (sizeof(int*) * 5);

    for (int i = 0; i < 5; i++)
        array[i] = malloc (sizeof(int) * 5);



    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++) {
            array[i][j] = (j + 1) * (i + 1);
            printf("%i", array[i][j]);
        }
        printf("\n");
    }


    int** buf = array;

    printf("%i\n", **array);
    *array++;

    printf("%i\n", **array);
    *array++;
     printf("%i\n", **array);
    *array++;


    array[0] = array[1];
    
    printf("%i\n", **array);
    *array++;
    
     printf("%i\n", **array);
    *array++;
    
     printf("%i\n", **array);
    *array++;

    array++;

     printf("%i\n", **array);
    *array++;
     printf("%i\n", **array);
    *array++;
     printf("%i\n", **array);
    *array++;
    






    





}
