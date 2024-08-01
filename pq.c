#include "pq.h"

struct pq {
    pq_item *items;
    int     *map;
    int      pq_size;
};

static void swap(PQ *p, int i, int j) {
    exch(p->items[i], p->items[j]);
    p->map[id(p->items[i])] = i;
    p->map[id(p->items[j])] = j;
}

void fix_up(PQ *p, int k) {
    while (k > 1 && more(p->items[k / 2], p->items[k])) {
        swap(p, k, k / 2);
        k = k / 2;
    }
}

void fix_down(PQ *p, int sz, int k) {
    while (2 * k <= sz) {
        int j = 2 * k;
        if (j < sz && more(p->items[j], p->items[j + 1])) {
            j++;
        }
        if (!more(p->items[k], p->items[j])) {
            break;
        }
        swap(p, k, j);
        k = j;
    }
}

PQ *pq_init(int pq_size) {
    PQ *p      = (PQ *)calloc(1, sizeof(PQ));
    p->items   = (pq_item *)malloc((pq_size + 1) * sizeof(pq_item));
    p->map     = (int *)malloc((pq_size + 1) * sizeof(int));
    p->pq_size = 0;
    return p;
}

void pq_insert(PQ *p, pq_item data) {
    p->pq_size += 1;
    p->items[p->pq_size] = data;
    p->map[id(data)]     = p->pq_size;
    fix_up(p, p->pq_size);
}

pq_item pq_pop_min(PQ *p) {
    pq_item min = p->items[1];
    swap(p, 1, p->pq_size);
    p->pq_size -= 1;
    fix_down(p, p->pq_size, 1);
    return min;
}
pq_item pq_min(PQ *p) {
    return p->items[1];
}
int pq_empty(PQ *p) {
    return p->pq_size == 0;
}
void pq_destroy(PQ *p) {
    free(p->items);
    free(p->map);
    free(p);
}
void pq_decrease_key(PQ *p, int id, Weight weight) {
    int i              = p->map[id];
    value(p->items[i]) = weight;
    fix_up(p, i);
}
pq_item pq_make_item(int id, Weight value) {
    pq_item t;
    id(t)    = id;
    value(t) = value;
    return t;
}
