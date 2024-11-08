#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "list.h"
#include "minheap.h"

int distance[MAX_VERTICES]; // 정점의 최단 거리 저장
int found[MAX_VERTICES]; // 정점의 방문 여부 저장
int foundOrder[MAX_VERTICES]; // 방문한 정점의 순서 저장
int foundIndex = 0;

// 그래프 초기화
void list_graph_init(GraphListType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj[i] = NULL;
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[0] = 0;
}

// 간선 추가
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

// 현재 상태 출력
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

// 최단 경로 탐색 (Dijkstra 알고리즘)
void list_shortest_path(GraphListType* g, int start) {
    MinHeap* minHeap = createMinHeap(g->n); // minheap 생성
    //초기화
    for (int v = 0; v < g->n; ++v) {
        distance[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, distance[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[start] = newMinHeapNode(start, distance[start]); // 시작 정점 힙 노드 생성
    minHeap->pos[start] = start; 
    distance[start] = 0; 
    updateDistance(minHeap, start, distance[start]); // 힙의 시작 정점 거리 업데이트

    minHeap->size = g->n; // 힙 크기를 정점 수로 설정

    while (minHeap->size != 0) {
        MinHeapNode* minHeapNode = removeMin(minHeap); // 힙에서 최단 거리 정점 추출
        int u = minHeapNode->vertex;

        found[u] = TRUE; // 선택된 정점을 방문으로 표시
        foundOrder[foundIndex++] = u + 1; // 방문한 정점 순서 기록

        list_print_status(g); // 현재 상태 출력

        GraphNode* node = g->adj[u]; // 선택된 정점의 인접 리스트 탐색
        while (node != NULL) {
            int v = node->vertex;

            // 인접 정점이 힙에 있으면, 최단 경로가 갱신될 경우 업데이트
            if (isInMinHeap(minHeap, v) && distance[u] != INF &&
                node->weight + distance[u] < distance[v]) {
                distance[v] = distance[u] + node->weight; // 더 짧은 경로 발견 시 거리 갱신
                updateDistance(minHeap, v, distance[v]); // 힙 거리 업데이트
            }
            node = node->next; // 다른 인접 정점으로 이동
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