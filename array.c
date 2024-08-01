#include "array.h"

int* array_init(int size) {
    int* a = malloc(size * sizeof(int));
    return a;
}

void array_destroy(int* a) {
    free(a);
}