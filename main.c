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

    Weight** rtt                = matrix_init(s, c);
    Weight** rtt_server_monitor = matrix_init(s, m);
    Weight** rtt_client_monitor = matrix_init(c, m);

    // S -> C
    for (int i = 0; i < s; i++) {
        Distance* d = dijkstra(graph, servers[i]);
        for (int j = 0; j < c; j++) {
            rtt[i][j] = d[clients[j]];
        }
        distance_destroy(d);
    }

    // C -> S
    for (int i = 0; i < c; i++) {
        Distance* d = dijkstra(graph, clients[i]);
        for (int j = 0; j < s; j++) {
            rtt[i][j] += d[servers[j]];
        }
        distance_destroy(d);
    }

    // S -> M
    for (int i = 0; i < s; i++) {
        Distance* d = dijkstra(graph, servers[i]);
        for (int j = 0; j < m; j++) {
            rtt_server_monitor[i][j] = d[monitors[j]];
        }
        distance_destroy(d);
    }

    // M -> S
    for (int i = 0; i < m; i++) {
        Distance* d = dijkstra(graph, monitors[i]);
        for (int j = 0; j < s; j++) {
            rtt_server_monitor[j][i] += d[servers[j]];
        }
        distance_destroy(d);
    }

    // C -> M
    for (int i = 0; i < c; i++) {
        Distance* d = dijkstra(graph, clients[i]);
        for (int j = 0; j < m; j++) {
            rtt_client_monitor[i][j] = d[monitors[j]];
        }
        distance_destroy(d);
    }

    // M -> C
    for (int i = 0; i < m; i++) {
        Distance* d = dijkstra(graph, monitors[i]);
        for (int j = 0; j < c; j++) {
            rtt_client_monitor[j][i] += d[clients[j]];
        }
        distance_destroy(d);
    }

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < c; j++) {
            Weight rtt_estimated =
                rtt_server_monitor[i][0] + rtt_client_monitor[0][j];
            for (int k = 1; k < m; k++) {
                Weight new_rtt =
                    rtt_server_monitor[i][k] + rtt_client_monitor[j][k];
                if (new_rtt < rtt_estimated) {
                    rtt_estimated = new_rtt;
                }
            }
            printf("%d %d %.10lf\n", servers[i], clients[j],
                   rtt_estimated / rtt[i][j]);
        }
    }

    matrix_destroy(rtt, s);
    matrix_destroy(rtt_client_monitor, s);
    matrix_destroy(rtt_server_monitor, c);
    graph_destroy(graph);

    return 0;
}
