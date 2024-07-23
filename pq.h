#ifndef PQ_H_
#define PQ_H_

#include "graph.h"

typedef Vertex   *pq_type;
typedef struct pq PQ;

PQ     *pq_init();
void    pq_insert(PQ *p, pq_type data);
pq_type pq_pop(PQ *p);
int     pq_empty(PQ *p);
void    pq_destroy(PQ *p);

#endif
