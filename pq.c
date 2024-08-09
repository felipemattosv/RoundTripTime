#include "pq.h"

#define PQSwap(A, B)  \
    {                 \
        PQItem t = A; \
        A        = B; \
        B        = t; \
    }

struct pq {
    PQItem *items;
    PQCmp   cmp;
    int     pq_size;
};

void fix_up(PQ *p, int k) {
    while (k > 1 && p->cmp(p->items[k / 2], p->items[k])) {
        PQSwap(p->items[k], p->items[k / 2]);
        k = k / 2;
    }
}

void fix_down(PQ *p, int sz, int k) {
    while (2 * k <= sz) {
        int j = 2 * k;
        if (j < sz && p->cmp(p->items[j], p->items[j + 1])) {
            j++;
        }
        if (!p->cmp(p->items[k], p->items[j])) {
            break;
        }
        PQSwap(p->items[k], p->items[j]);
        k = j;
    }
}

PQ *pq_init(int pq_size, PQCmp cmp) {
    PQ *p      = (PQ *)calloc(1, sizeof(PQ));
    p->items   = (PQItem *)malloc((pq_size + 1) * sizeof(PQItem));
    p->cmp     = cmp;
    p->pq_size = 0;
    return p;
}

void pq_destroy(PQ *p) {
    free(p->items);
    free(p);
}

void pq_insert(PQ *p, PQItem data) {
    p->pq_size += 1;
    p->items[p->pq_size] = data;
    fix_up(p, p->pq_size);
}

PQItem pq_pop_min(PQ *p) {
    PQItem min = p->items[1];
    PQSwap(p->items[1], p->items[p->pq_size]);
    p->pq_size -= 1;
    fix_down(p, p->pq_size, 1);
    return min;
}

PQItem pq_min(PQ *p) {
    return p->items[1];
}

int pq_empty(PQ *p) {
    return p->pq_size == 0;
}
