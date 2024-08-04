#include "matrix.h"

Weight **matrix_init(int l, int c) {
    Weight **m = (Weight **)malloc(l * sizeof(Weight *));
    for (int i = 0; i < l; i++) m[i] = (Weight *)calloc(c, sizeof(Weight));
    return m;
}

void matrix_rtt_fill(Weight **m, int a_size, int *a, Distance **distA,
                     int b_size, int *b, Distance **distB) {
    // A -> B
    for (int i = 0; i < a_size; i++) {
        for (int j = 0; j < b_size; j++) {
            m[i][j] = distA[i][b[j]];
        }
    }

    // B -> A
    for (int i = 0; i < b_size; i++) {
        for (int j = 0; j < a_size; j++) {
            m[j][i] += distB[i][a[j]];
        }
    }
}

void matrix_destroy(Weight **m, int l) {
    for (int i = 0; i < l; i++) free(m[i]);
    free(m);
}

void matrix_show(Weight **m, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%lf ", m[i][j]);
        }
        printf("\n");
    }
}