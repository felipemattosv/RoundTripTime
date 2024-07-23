#include "graph.h"

int main(int argc, char** argv) {
    int v_size = 5;
    int e_size = 9;

    Graph* graph = graph_init(v_size);

    for (int i = 0; i < e_size; i++) {
        int    origin, destiny;
        Weight weight;
        scanf("%d %d %lf", &origin, &destiny, &weight);
        Edge* edge = edge_init(origin, destiny, weight);
        graph_add_edge(graph, edge);
    }

    graph_show(graph);
    graph_destroy(graph);

    return 0;
}