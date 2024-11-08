#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "list.h"
#include "minheap.h"

int distance[MAX_VERTICES]; // ������ �ִ� �Ÿ� ����
int found[MAX_VERTICES]; // ������ �湮 ���� ����
int foundOrder[MAX_VERTICES]; // �湮�� ������ ���� ����
int foundIndex = 0;

// �׷��� �ʱ�ȭ
void list_graph_init(GraphListType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj[i] = NULL;
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[0] = 0;
}

// ���� �߰�
void list_insert_edge(GraphListType* g, int start, int end, int w) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = end - 1;
    node->weight = w;
    node->next = g->adj[start - 1];
    g->adj[start - 1] = node;

    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = start - 1;
    node->weight = w;
    node->next = g->adj[end - 1];
    g->adj[end - 1] = node;

    if (g->n < start) g->n = start;
    if (g->n < end) g->n = end;
}

// ���� ���� ���
void list_print_status(GraphListType* g) {
    printf("Distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) {
            printf("* ");
        }
        else {
            printf("%d ", distance[i]);
        }
    }
    printf("\nFound: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

// �ִ� ��� Ž�� (Dijkstra �˰���)
void list_shortest_path(GraphListType* g, int start) {
    MinHeap* minHeap = createMinHeap(g->n); // minheap ����
    //�ʱ�ȭ
    for (int v = 0; v < g->n; ++v) {
        distance[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, distance[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[start] = newMinHeapNode(start, distance[start]); // ���� ���� �� ��� ����
    minHeap->pos[start] = start; 
    distance[start] = 0; 
    updateDistance(minHeap, start, distance[start]); // ���� ���� ���� �Ÿ� ������Ʈ

    minHeap->size = g->n; // �� ũ�⸦ ���� ���� ����

    while (minHeap->size != 0) {
        MinHeapNode* minHeapNode = removeMin(minHeap); // ������ �ִ� �Ÿ� ���� ����
        int u = minHeapNode->vertex;

        found[u] = TRUE; // ���õ� ������ �湮���� ǥ��
        foundOrder[foundIndex++] = u + 1; // �湮�� ���� ���� ���

        list_print_status(g); // ���� ���� ���

        GraphNode* node = g->adj[u]; // ���õ� ������ ���� ����Ʈ Ž��
        while (node != NULL) {
            int v = node->vertex;

            // ���� ������ ���� ������, �ִ� ��ΰ� ���ŵ� ��� ������Ʈ
            if (isInMinHeap(minHeap, v) && distance[u] != INF &&
                node->weight + distance[u] < distance[v]) {
                distance[v] = distance[u] + node->weight; // �� ª�� ��� �߰� �� �Ÿ� ����
                updateDistance(minHeap, v, distance[v]); // �� �Ÿ� ������Ʈ
            }
            node = node->next; // �ٸ� ���� �������� �̵�
        }
    }

    printf("Found Order: ");
    for (int i = 0; i < foundIndex; i++) {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}

void list_GenerateGraph(GraphListType* g) {
    list_insert_edge(g, 1, 2, 3);
    list_insert_edge(g, 1, 6, 11);
    list_insert_edge(g, 1, 7, 12);
    list_insert_edge(g, 2, 3, 5);
    list_insert_edge(g, 2, 4, 4);
    list_insert_edge(g, 2, 5, 1);
    list_insert_edge(g, 2, 6, 7);
    list_insert_edge(g, 2, 7, 8);
    list_insert_edge(g, 3, 4, 2);
    list_insert_edge(g, 3, 7, 6);
    list_insert_edge(g, 3, 8, 5);
    list_insert_edge(g, 4, 5, 13);
    list_insert_edge(g, 4, 8, 14);
    list_insert_edge(g, 4, 10, 16);
    list_insert_edge(g, 5, 6, 9);
    list_insert_edge(g, 5, 9, 18);
    list_insert_edge(g, 5, 10, 17);
    list_insert_edge(g, 7, 8, 13);
    list_insert_edge(g, 8, 10, 15);
    list_insert_edge(g, 9, 10, 10);
}