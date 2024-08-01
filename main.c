#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"
#include "graph.h"
#include "matrix.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: %s 'input.txt' 'output.txt'", argv[0]);
        exit(0);
    }

    /*
     * Redirect file to stdin and stdout.
     */
    freopen(argv[1], "r", stdin);
    //freopen(argv[2], "w", stdout);

    int v_size, e_size;

    /*
     * S -> Server
     * C -> Client
     * M -> Monitor
     */
    int s, c, m;

    scanf("%d %d", &v_size, &e_size);
    scanf("%d %d %d", &s, &c, &m);

    int servers[s];
    int clients[c];
    int monitors[m];

    for (int i = 0; i < s; i++) {
        scanf("%d", &servers[i]);
    }
    for (int i = 0; i < c; i++) {
        scanf("%d", &clients[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &monitors[i]);
    }

    Graph* graph = graph_init(v_size);

    for (int i = 0; i < e_size; i++) {
        int    origin, destiny;
        Weight weight;
        scanf("%d %d %lf", &origin, &destiny, &weight);
        Edge* edge = edge_init(destiny, weight);
        graph_add_edge(graph, origin, edge);
    }

    Weight **rtt = matrix_init(s, c);
    

    for (int i = 0; i < s; i++) {
        Distance* d = dijkstra(graph, servers[i]);
        for (int j = 0; j < c; j++) {
            rtt[i][j] = d[clients[j]];

        }
        distance_destroy(d);
    }

    for (int i = 0; i < c; i++) {
        Distance* d = dijkstra(graph, clients[i]);
        for (int j = 0; j < s; j++) {
            rtt[i][j] += d[servers[j]];
        }
        distance_destroy(d);
    }

    for (int i =0; i < s; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d x %d =  %lf\n", servers[i], clients[j], rtt[i][j]);
        }
    }

    matrix_destroy(rtt, s);

    //graph_show(graph);
    graph_destroy(graph);

    return 0;
}
