#include <stdio.h>
#include "getch.h"




void main(void)

{
    while (1)
    {
        printf("Input: ");
        int a = getch();

        printf("%i\n", a);
    }

}
