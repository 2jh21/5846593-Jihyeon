#pragma once

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphMatType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

void matrix_graph_init(GraphMatType* g);
void matrix_insert_edge(GraphMatType* g, int start, int end, int w);
int matrix_choose(int distance[], int n, int found[]);
void matrix_print_status(GraphMatType* g);
void matrix_shortest_path(GraphMatType* g, int start);
void matrix_generate_graph(GraphMatType* g);