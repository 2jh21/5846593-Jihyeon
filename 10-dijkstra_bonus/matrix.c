#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "matrix.h"

int distance[MAX_VERTICES]; // 정점의 최단 거리 저장
int found[MAX_VERTICES]; // 정점의 방문 여부 저장
int found_order[MAX_VERTICES]; // 방문한 정점의 순서 저장
int found_index = 0;

// 그래프 초기화
void matrix_graph_init(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;
        }
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[0] = 0;
}

// 간선 추가
void matrix_insert_edge(GraphMatType* g, int start, int end, int w) {
    g->weight[start - 1][end - 1] = w;
    g->weight[end - 1][start - 1] = w;
    if (g->n < start) g->n = start;
    if (g->n < end) g->n = end;
}

// 최단 거리 정점 선택
int matrix_choose(int distance[], int n, int found[]) {
    int min = INT_MAX, minpos = -1;
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 현재 상태 출력
void matrix_print_status(GraphMatType* g) {
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
void matrix_shortest_path(GraphMatType* g, int start) {
    // 초기화
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    found_index = 0;
    found[start] = TRUE;
    distance[start] = 0;
    found_order[found_index++] = start; // 시작 정점 순서 저장

    matrix_print_status(g); // 초기 상태 출력

    // 시작 정점과 직접 연결된 정점들의 거리 설정
    for (int i = 0; i < g->n; i++) {
        if (g->weight[start][i] < INF) distance[i] = g->weight[start][i];
    }

    // 모든 정점을 돌며 최단 경로 탐색
    for (int i = 0; i < g->n - 1; i++) {
        int u = matrix_choose(distance, g->n, found); // 최단 거리가 있는 정점 선택
        if (u == -1) break; // 더 이상 방문할 정점이 없을 때 종료
        found[u] = TRUE; // 선택된 정점을 방문으로 표시
        found_order[found_index++] = u; // 방문 순서 저장

        matrix_print_status(g); // 현재 상태 출력

        // 선택된 정점을 통해 다른 정점으로 가는 최단 경로 업데이트
        for (int w = 0; w < g->n; w++)
            if (!found[w] && distance[u] + g->weight[u][w] < distance[w])
                distance[w] = distance[u] + g->weight[u][w];
    }

    printf("Found Order: ");
    for (int i = 0; i < found_index; i++) {
        printf("%d ", found_order[i] + 1);
    }
    printf("\n");
}

void matrix_generate_graph(GraphMatType* g) {
    matrix_insert_edge(g, 1, 2, 3);
    matrix_insert_edge(g, 1, 6, 11);
    matrix_insert_edge(g, 1, 7, 12);
    matrix_insert_edge(g, 2, 3, 5);
    matrix_insert_edge(g, 2, 4, 4);
    matrix_insert_edge(g, 2, 5, 1);
    matrix_insert_edge(g, 2, 6, 7);
    matrix_insert_edge(g, 2, 7, 8);
    matrix_insert_edge(g, 3, 4, 2);
    matrix_insert_edge(g, 3, 7, 6);
    matrix_insert_edge(g, 3, 8, 5);
    matrix_insert_edge(g, 4, 5, 13);
    matrix_insert_edge(g, 4, 8, 14);
    matrix_insert_edge(g, 4, 10, 16);
    matrix_insert_edge(g, 5, 6, 9);
    matrix_insert_edge(g, 5, 9, 18);
    matrix_insert_edge(g, 5, 10, 17);
    matrix_insert_edge(g, 7, 8, 13);
    matrix_insert_edge(g, 8, 10, 15);
    matrix_insert_edge(g, 9, 10, 10);
}
