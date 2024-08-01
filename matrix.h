#ifndef MATRIX_H
#define MATRIX_H

#include "graph.h"
#include <stdlib.h>

Weight** matrix_init(int l, int c);
void matrix_destroy(Weight **m, int l);

#endif