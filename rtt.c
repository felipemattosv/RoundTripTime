#include "rtt.h"

struct rtt_inflation {
    int    a, b;
    Weight time;
};

RTTInflation* rtt_inflation_init(int a, int b, Weight time) {
    RTTInflation* ri = malloc(sizeof(RTTInflation));

    ri->a    = a;
    ri->b    = b;
    ri->time = time;

    return ri;
}

int rtt_inflation_a(RTTInflation* ri) {
    return ri->a;
}

int rtt_inflation_b(RTTInflation* ri) {
    return ri->b;
}

Weight rtt_inflation_time(RTTInflation* ri) {
    return ri->time;
}

int rtt_inflation_cmp(void* a, void* b) {
    RTTInflation* a1 = a;
    RTTInflation* b1 = b;
    return a1->time > b1->time;
}

void graph_read_edges(Graph* g, int e_size) {
    for (int i = 0; i < e_size; i++) {
        int    origin, destiny;
        Weight weight;
        scanf("%d %d %lf", &origin, &destiny, &weight);
        Edge* edge = edge_init(destiny, weight);
        graph_add_edge(g, origin, edge);
    }
}
