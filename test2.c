#include <stdio.h>
#include <stdlib.h>



typedef struct {

    int a;
} Test;



void main(void)
{
   Test* test = malloc (sizeof(Test));


   Test* test1;

   test1 = test;

   test -> a = 5;

   test1 -> a = 10;

   printf("%i\n", test -> a);


}
