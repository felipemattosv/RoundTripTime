#include "array.h"

int* array_init(int size) {
    int* a = malloc(size * sizeof(int));
    return a;
}

void array_read(int size) {
    int* a = array_init(size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &a[i]);
    }
    return a;
}

void array_destroy(int* a) {
    free(a);
}