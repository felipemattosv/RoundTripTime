#include "graph.h"

#define INITIAL_CAP_EDGES 100
#define REALLOC_FACTOR 2

struct vertex {
    Edge** edges;
    int    e_size;
    int    allocated_edges;
};

struct edge {
    int    destiny;
    Weight weight;
};

struct graph {
    Vertex** vertexes;
    int      v_size;
};

// Vertex functions:

Vertex* vertex_init() {
    Vertex* v = calloc(1, sizeof(Vertex));

    v->e_size          = 0;
    v->allocated_edges = INITIAL_CAP_EDGES;
    v->edges           = (Edge**)malloc(v->allocated_edges * sizeof(Edge*));

    return v;
}

void vertex_destroy(Vertex* v) {
    for (int i = 0; i < v->e_size; i++) {
        edge_destroy(v->edges[i]);
    }
    free(v->edges);
    free(v);
}

void vertex_add_edge(Vertex* v, Edge* e) {
    if (v->allocated_edges == v->e_size) {
        v->allocated_edges *= REALLOC_FACTOR;
        v->edges =
            (Edge**)realloc(v->edges, v->allocated_edges * sizeof(Edge*));
    }

    v->edges[v->e_size++] = e;
}

int vertex_edges_size(Vertex* v) {
    return v->e_size;
}

Edge* vertex_edge_at(Vertex* v, int k) {
    return v->edges[k];
}

// Edge functions:

Edge* edge_init(int destiny, Weight w) {
    Edge* e = (Edge*)calloc(1, sizeof(Edge));

    e->destiny = destiny;
    e->weight  = w;

    return e;
}

int edge_get_dest(Edge* e) {
    return e->destiny;
}

Weight edge_get_weight(Edge* e) {
    return e->weight;
}

void edge_destroy(Edge* e) {
    free(e);
}

// Graph functions:

Graph* graph_init(int v_size) {
    Graph* g = (Graph*)calloc(1, sizeof(Graph));

    g->v_size   = v_size;
    g->vertexes = (Vertex**)malloc(v_size * sizeof(Vertex*));

    for (int i = 0; i < v_size; i++) {
        g->vertexes[i] = vertex_init();
    }

    return g;
}

void graph_read(Graph* g, int e_size) {
    for (int i = 0; i < e_size; i++) {
        int    origin, destiny;
        Weight weight;
        scanf("%d %d %lf", &origin, &destiny, &weight);
        Edge* edge = edge_init(destiny, weight);
        graph_add_edge(g, origin, edge);
    }
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
        int edges_size = vertex_edges_size(g->vertexes[i]);
        for (int j = 0; j < edges_size; j++) {
            Edge* e = vertex_edge_at(g->vertexes[i], j);
            printf("  Edge %d -> %d (%lf)\n", i, e->destiny, e->weight);
        }
    }
}
