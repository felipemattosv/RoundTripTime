#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "pq.h"

typedef Weight Distance;

Distance  *distance_init(int d_size);
void       distance_destroy(Distance *d);
Distance **distances_calculate(Graph *g, int *origins, int o_size);
void       distances_destroy(Distance **d, int d_size);
Distance  *dijkstra(Graph *g, int origin);

#endif
