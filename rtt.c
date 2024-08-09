#include "rtt.h"

void graph_read(Graph* g, int e_size) {
    for (int i = 0; i < e_size; i++) {
        int    origin, destiny;
        Weight weight;
        scanf("%d %d %lf", &origin, &destiny, &weight);
        Edge* edge = edge_init(destiny, weight);
        graph_add_edge(g, origin, edge);
    }
}
