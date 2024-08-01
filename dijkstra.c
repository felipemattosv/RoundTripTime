#include "dijkstra.h"

#include "graph.h"
#define DIST_INF 0x3f3f3f3f

Distance *distance_init(int d_size) {
    Distance *d = (Distance *)malloc(sizeof(Distance) * d_size);
    return d;
}

void distance_destroy(Distance *d) {
    free(d);
}

Distance *dijkstra(Graph *g, int origin) {
    Distance *dist = distance_init(graph_vertex_size(g));

    for (int i = 0; i < graph_vertex_size(g); i++) {
        dist[i] = DIST_INF;
    }

    dist[origin] = 0;

    PQ *pq = pq_init(graph_vertex_size(g));
    pq_insert(pq, pq_make_item(origin, 0));

    while (!pq_empty(pq)) {
        pq_item U = pq_pop_min(pq);
        Vertex *V = graph_get_vertex(g, id(U));

        for (int i = 0; i < vertex_edges_size(V); i++) {
            Edge  *e    = vertex_edge_at(V, i);
            Weight cost = edge_get_weight(e);
            int    dest = edge_get_dest(e);
            graph_vertex_visit(g, id(U));
            Distance distance = dist[id(U)] + cost;
            if (distance < dist[dest]) {
                dist[dest] = distance;
                pq_insert(pq, pq_make_item(dest, distance));
            }
        }
    }

    pq_destroy(pq);

    return dist;
}
