#ifndef RTT_H
#define RTT_H

#include <stdlib.h>

#include "graph.h"

typedef struct rtt_inflation RTTInflation;

RTTInflation* rtt_inflation_init(int a, int b, Weight time);
int           rtt_inflation_a(RTTInflation* ri);
int           rtt_inflation_b(RTTInflation* ri);
Weight        rtt_inflation_time(RTTInflation* ri);
int           rtt_inflation_cmp(void* a, void* b);

void graph_read(Graph* g, int e_size);

#endif