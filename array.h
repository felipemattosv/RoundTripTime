#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef int* Array;

int* array_init(int size);
void array_destroy(int* a);

#endif
