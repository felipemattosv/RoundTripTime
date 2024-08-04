#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#include "dijkstra.h"
#include "graph.h"

Weight **matrix_init(int l, int c);
void     matrix_rtt_fill(Weight **m, int a_size, int *a, Distance **distA,
                         int b_size, int *b, Distance **distB);
void     matrix_destroy(Weight **m, int l);

// debug only:
void matrix_show(Weight **m, int l, int c);

#endif