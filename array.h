#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef int* Array;

int* array_init(int size);
int* array_read(int size);
void array_destroy(int* a);

#endif
