#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "dijkstra.h"
#include "graph.h"
#include "matrix.h"
#include "rtt.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: %s 'input.txt' 'output.txt'\n", argv[0]);
        exit(0);
    }

    // Redirect file to stdin and stdout.
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    // Read input
    int v_size, e_size;
    int s, c, m;

    scanf("%d %d", &v_size, &e_size);
    scanf("%d %d %d", &s, &c, &m);

    int* servers  = array_read(s);
    int* clients  = array_read(c);
    int* monitors = array_read(m);

    Graph* graph = graph_init(v_size);

    graph_read_edges(graph, e_size);

    // Calculate RTT
    Weight** rtt                = matrix_init(s, c);
    Weight** rtt_server_monitor = matrix_init(s, m);
    Weight** rtt_client_monitor = matrix_init(c, m);

    Distance** servers_distances  = distances_calculate(graph, servers, s);
    Distance** clients_distances  = distances_calculate(graph, clients, c);
    Distance** monitors_distances = distances_calculate(graph, monitors, m);

    matrix_rtt_fill(rtt, s, servers, servers_distances, c, clients,
                    clients_distances);
    matrix_rtt_fill(rtt_server_monitor, s, servers, servers_distances, m,
                    monitors, monitors_distances);
    matrix_rtt_fill(rtt_client_monitor, c, clients, clients_distances, m,
                    monitors, monitors_distances);

    // Calculate inflation
    PQ* rtt_inflation = pq_init(s * c, rtt_inflation_cmp);

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

            int    a    = servers[i];
            int    b    = clients[j];
            Weight time = rtt_estimated / rtt[i][j];

            pq_insert(rtt_inflation, rtt_inflation_init(a, b, time));
        }
    }

    while (!pq_empty(rtt_inflation)) {
        RTTInflation* inflation = pq_pop_min(rtt_inflation);

        int    a    = rtt_inflation_a(inflation);
        int    b    = rtt_inflation_b(inflation);
        Weight time = rtt_inflation_time(inflation);

        printf("%d %d %.16lf\n", a, b, time);
        free(inflation);
    }

    // Free memory
    pq_destroy(rtt_inflation);
    distances_destroy(servers_distances, s);
    distances_destroy(clients_distances, c);
    distances_destroy(monitors_distances, m);
    matrix_destroy(rtt, s);
    matrix_destroy(rtt_server_monitor, s);
    matrix_destroy(rtt_client_monitor, c);
    array_destroy(servers);
    array_destroy(clients);
    array_destroy(monitors);
    graph_destroy(graph);

    return 0;
}
