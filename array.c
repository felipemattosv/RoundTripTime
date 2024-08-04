#include "array.h"

int* array_init(int size) {
    int* a = malloc(size * sizeof(int));
    return a;
}

void array_read(int* a, int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &a[i]);
    }
}

void array_destroy(int* a) {
    free(a);
}