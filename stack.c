#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void push(Buffer a, int value)
{
    for (int i = 0; i < a.size - 1; i++)
       a.buffer[i] = a.buffer[i + 1];

    a.buffer[a.size - 1] = value;
}

int pop(Buffer a)
{

    int value = a.buffer[a.size - 1];

    for (int i = a.size - 1; i >= 0; i--)
       a.buffer[i] = a.buffer[i - 1];

    return value;  
}

void print(Buffer a)
{
    for (int i = 0; i < a.size; i++)
        printf("%i\n", a.buffer[i]);
}

bool isEmpty(Buffer a)
{
    for (int i = 0; i < a.size - 1; i++)
        if (a.buffer[i] != 0)
            return false;

    return true;
}
