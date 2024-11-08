#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "list.h"


int main(void) {
    GraphMatType* g_mat = (GraphMatType*)malloc(sizeof(GraphMatType));
    matrix_graph_init(g_mat);
    matrix_generate_graph(g_mat);
    printf("\n---------------인접 행렬---------------\n\n");
    matrix_shortest_path(g_mat, 0);
    free(g_mat);

    printf("\n\n----------인접 리스트(MinHeap)----------\n\n");
    GraphListType* g_list = (GraphListType*)malloc(sizeof(GraphListType));
    list_graph_init(g_list);
    list_GenerateGraph(g_list);
    list_shortest_path(g_list, 0);
    free(g_list);
    return 0;
    return 0;
}
