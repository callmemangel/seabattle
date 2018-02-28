#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int* buffer;
    int size;
} Buffer;

void push(Buffer a, int value);

int pop(Buffer a);

void print(Buffer a);

bool isEmptyBuffer(Buffer a);

#endif
