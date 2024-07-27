#ifndef PQ_H_
#define PQ_H_

#include "graph.h"

typedef struct pq PQ;

typedef struct {
    int    id;
    Weight value;
} pq_item;

#define id(A) (A.id)
#define value(A) (A.value)
#define more(A, B) (value(A) > value(B))
#define exch(A, B)     \
    {                  \
        pq_item t = A; \
        A         = B; \
        B         = t; \
    }

PQ     *pq_init(int pq_size);
void    pq_insert(PQ *p, pq_item data);
pq_item pq_pop_min(PQ *p);
pq_item pq_min(PQ *p);
int     pq_empty(PQ *p);
void    pq_destroy(PQ *p);
void    pq_decrease_key(PQ *p, int id, Weight weight);
pq_item pq_make_item(int id, Weight value);

#endif
