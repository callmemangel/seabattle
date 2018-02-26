#include <stdio.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32mHELLO WORLD"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int main()
{
//    printf("%sgreen\n", KGRN);
//    printf("%syellow\n", KYEL);
//    printf("%sblue\n", KBLU);
//    printf("%smagenta\n", KMAG);
//    printf("%scyan\n", KCYN);
//    printf("%swhite\n", KWHT);
//    printf("%snormal\n", KNRM);

    printf("\033[%imhello\033[0m\n",30);
    printf("\033[%im%shello\033[0m\n",31, "");
    printf("\033[%imhello\033[0m\n",32);
    printf("\033[%imhello\033[0m\n",33);
    printf("\033[%imhello\033[0m\n",34);
    printf("\033[%imhello\033[0m\n",35);
    printf("\033[%imhello\033[0m\n",36);
    printf("\033[%imhello\033[0m\n",37);
 
      char *a = "\x1B[32m";
     

      printf("%i\n", strlen(a));

    return 0;
}
