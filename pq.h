#ifndef PQ_H_
#define PQ_H_

#include "graph.h"

typedef struct pq PQ;

typedef void *PQItem;
typedef int (*PQCmp)(void *a, void *b);

// #define id(A) (A.id)
// #define value(A) (A.value)
// #define more(A, B) (value(A) > value(B))
// #def ine  exch(A, B)    \
//    {                 \
//        PQItem t = A; \
//        A        = B; \
//        B        = t; \
//    }

PQ  *pq_init(int pq_size, PQCmp cmp);
void pq_destroy(PQ *p);

void   pq_insert(PQ *p, PQItem data);
PQItem pq_pop_min(PQ *p);
PQItem pq_min(PQ *p);
int    pq_empty(PQ *p);

#endif
