#include "graph.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: %s 'input.txt' 'output.txt'", argv[0]);
        exit(0);
    }

    /*
     * Redirect file to stdin and stdout.
     */
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    int v_size, e_size;

    /*
     * S -> Server
     * C -> Client
     * M -> Monitor
     */
    int s, c, m;

    scanf("%d %d", &v_size, &e_size);
    scanf("%d %d %d", &s, &c, &m);

    for (int i = 0; i < s; i++) {
        scanf("%*d");
    }
    for (int i = 0; i < c; i++) {
        scanf("%*d");
    }
    for (int i = 0; i < m; i++) {
        scanf("%*d");
    }

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
