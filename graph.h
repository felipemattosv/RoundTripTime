#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef double        Weight;
typedef struct vertex Vertex;
typedef struct edge   Edge;
typedef struct graph  Graph;

/*
 *  A interface para o vertex
 *  Vertex é uma estrutura que contém um vetor de edges.
 */
Vertex* vertex_init();
void    vertex_destroy(Vertex* v);
void    vertex_add_edge(Vertex* v, Edge* e);
int     vertex_edges_size(Vertex* v);
Edge*   vertex_edge_at(Vertex* v, int k);

/*
 *  A interface para o edge
 *  Um edge tem uma origem e um destino e um peso.
 */
Edge*  edge_init(int destiny, Weight w);
int    edge_get_dest(Edge* e);
Weight edge_get_weight(Edge* e);
void   edge_destroy(Edge* e);

/*
 *  A interface para o graph
 *  Um graph tem a estrutura para os vertexes e
 *  para dizer se um vertex já foi visitado.
 */
Graph*  graph_init(int v_size);
void    graph_read(Graph* g, int e_size);
void    graph_destroy(Graph* g);
Vertex* graph_get_vertex(Graph* g, int k);
int     graph_vertex_size(Graph* g);
void    graph_add_edge(Graph* g, int origin, Edge* e);
void    graph_show(Graph* g);

#endif
