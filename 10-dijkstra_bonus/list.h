#pragma once

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* next;
} GraphNode;

typedef struct GraphListType {
    int n;
    GraphNode* adj[MAX_VERTICES];
} GraphListType;

void list_graph_init(GraphListType* g);
void list_insert_edge(GraphListType* g, int start, int end, int w);
void list_print_status(GraphListType* g);
void list_shortest_path(GraphListType* g, int start);
void list_GenerateGraph(GraphListType* g);