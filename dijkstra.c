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

Distance **distances_calculate(Graph *g, int *origins, int o_size) {
    Distance **distances = (Distance **)malloc(sizeof(Distance *) * o_size);
    for (int i = 0; i < o_size; i++) {
        distances[i] = dijkstra(g, origins[i]);
    }
    return distances;
}

void distances_destroy(Distance **d, int d_size) {
    for (int i = 0; i < d_size; i++) {
        distance_destroy(d[i]);
    }
    free(d);
}

typedef struct {
    int    id;
    Weight weight;
} DijkstraItem;

DijkstraItem *dijkstra_item(int id, Weight w) {
    DijkstraItem *di = malloc(sizeof(DijkstraItem));

    di->id     = id;
    di->weight = w;

    return di;
}

int dijkstra_item_cmp(void *a, void *b) {
    DijkstraItem *a1 = a;
    DijkstraItem *b1 = b;
    return a1->weight > b1->weight;
}

Distance *dijkstra(Graph *g, int origin) {
    Distance *dist = distance_init(graph_vertex_size(g));

    for (int i = 0; i < graph_vertex_size(g); i++) {
        dist[i] = DIST_INF;
    }

    dist[origin] = 0;

    PQ *pq = pq_init(graph_vertex_size(g), dijkstra_item_cmp);

    pq_insert(pq, dijkstra_item(origin, 0));

    while (!pq_empty(pq)) {
        DijkstraItem *U     = pq_pop_min(pq);
        Vertex       *V     = graph_get_vertex(g, U->id);
        List         *edges = vertex_edges(V);

        for (List *i = edges; i != NULL; i = list_next(i)) {
            Edge    *e        = list_item(i);
            Weight   cost     = edge_get_weight(e);
            int      dest     = edge_get_dest(e);
            Distance distance = dist[U->id] + cost;
            if (distance < dist[dest]) {
                dist[dest] = distance;
                pq_insert(pq, dijkstra_item(dest, distance));
            }
        }
        free(U);
    }

    pq_destroy(pq);

    return dist;
}
