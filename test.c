#include <stdio.h>




void main(void)
{
    for (int i = 0; i < 256; i++)
    {
        printf("%i - \033[34;%imtext\033[0m\n", i, i);
    }

}
