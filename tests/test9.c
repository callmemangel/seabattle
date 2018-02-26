#include <stdio.h>



void swap(int *a, int* b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;

}

void main(void)
{
    int a = 5;
    int b = 4;

    swap(&a, &b);

    printf("%i\n", a);
    printf("%i\n", b);


}
