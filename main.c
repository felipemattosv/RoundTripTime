#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "dijkstra.h"
#include "graph.h"
#include "matrix.h"

typedef struct {
    int    a, b;
    Weight w;
} rtt_err;

int rtt_cmp(const void* a, const void* b) {
    rtt_err* aa   = (rtt_err*)a;
    rtt_err* bb   = (rtt_err*)b;
    Weight   diff = aa->w - bb->w;
    if (diff > 0)
        return 1;
    else
        return -1;
}

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

    int s, c, m;

    scanf("%d %d", &v_size, &e_size);
    scanf("%d %d %d", &s, &c, &m);

    int* servers  = array_init(s);
    int* clients  = array_init(c);
    int* monitors = array_init(m);

    array_read(servers, s);
    array_read(clients, c);
    array_read(monitors, m);

    Graph* graph = graph_init(v_size);

    graph_read(graph, e_size);

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
            rtt[j][i] += d[servers[j]];
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

    rtt_err* err = malloc(sizeof(rtt_err) * s * c);

    int count = 0;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < c; j++) {
            Weight rtt_estimated =
                rtt_server_monitor[i][0] + rtt_client_monitor[j][0];
            for (int k = 1; k < m; k++) {
                Weight new_rtt =
                    rtt_server_monitor[i][k] + rtt_client_monitor[j][k];
                if (new_rtt < rtt_estimated) {
                    rtt_estimated = new_rtt;
                }
            }
            err[count++] = (rtt_err){.a = servers[i],
                                     .b = clients[j],
                                     .w = rtt_estimated / rtt[i][j]};
        }
    }

    qsort(err, s * c, sizeof(rtt_err), rtt_cmp);

    for (int i = 0; i < s * c; i++) {
        printf("%d %d %.16lf\n", err[i].a, err[i].b, err[i].w);
    }

    free(err);
    matrix_destroy(rtt, s);
    matrix_destroy(rtt_client_monitor, s);
    matrix_destroy(rtt_server_monitor, c);
    array_destroy(servers);
    array_destroy(clients);
    array_destroy(monitors);
    graph_destroy(graph);

    return 0;
}
