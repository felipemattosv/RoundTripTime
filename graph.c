#include "graph.h"

struct vertex {
    List* edges;
};

struct edge {
    int    destiny;
    Weight weight;
};

struct graph {
    Vertex** vertexes;
    int      v_size;
};

// Vertex functions

Vertex* vertex_init() {
    Vertex* v = calloc(1, sizeof(Vertex));

    v->edges = list_init();

    return v;
}

void vertex_destroy(Vertex* v) {
    for (List* i = v->edges; i != NULL; i = list_next(i)) {
        edge_destroy(list_item(i));
    }

    list_destroy(v->edges);
    free(v);
}

void vertex_add_edge(Vertex* v, Edge* e) {
    v->edges = list_push_front(v->edges, e);
}

List* vertex_edges(Vertex* v) {
    return v->edges;
}

// Edge functions

Edge* edge_init(int destiny, Weight w) {
    Edge* e = (Edge*)calloc(1, sizeof(Edge));

    e->destiny = destiny;
    e->weight  = w;

    return e;
}

void edge_destroy(Edge* e) {
    free(e);
}

int edge_get_dest(Edge* e) {
    return e->destiny;
}

Weight edge_get_weight(Edge* e) {
    return e->weight;
}

// Graph functions

Graph* graph_init(int v_size) {
    Graph* g = (Graph*)calloc(1, sizeof(Graph));

    g->v_size   = v_size;
    g->vertexes = (Vertex**)malloc(v_size * sizeof(Vertex*));

    for (int i = 0; i < v_size; i++) {
        g->vertexes[i] = vertex_init();
    }

    return g;
}

void graph_destroy(Graph* g) {
    for (int i = 0; i < g->v_size; i++) {
        vertex_destroy(g->vertexes[i]);
    }

    free(g->vertexes);
    free(g);
}

Vertex* graph_get_vertex(Graph* g, int k) {
    return g->vertexes[k];
}

int graph_vertex_size(Graph* g) {
    return g->v_size;
}

void graph_add_edge(Graph* g, int origin, Edge* e) {
    vertex_add_edge(g->vertexes[origin], e);
}

void graph_show(Graph* g) {
    for (int i = 0; i < g->v_size; i++) {
        printf("Vertex %d\n", i);
        List* edges = vertex_edges(g->vertexes[i]);
        for (List* j = edges; j != NULL; j = list_next(j)) {
            Edge* e = list_item(j);
            printf("  Edge %d -> %d (%lf)\n", i, e->destiny, e->weight);
        }
    }
}
