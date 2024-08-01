#include "matrix.h"

Weight** matrix_init(int l, int c) {
    Weight **m = (Weight **)malloc(l * sizeof(Weight*));
    for (int i = 0; i < l; i++)
        m[i] = (Weight *)calloc(c, sizeof(Weight*));
    return m;
}


void matrix_destroy(Weight **m, int l) {
    for (int i = 0; i < l; i++)
        free(m[i]);
    free(m);
}
