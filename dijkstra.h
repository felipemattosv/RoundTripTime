#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "pq.h"

typedef Weight Distance;

Distance *distance_init(int d_size);
void      distance_destroy(Distance *d);
Distance *dijkstra(Graph *g, int origin);

#endif
