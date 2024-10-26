#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = 0; 
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;
        }
        distance[i] = INF;
        selected[i] = FALSE;
    }
    distance[0] = 0;
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start - 1][end - 1] = w; // 시작 정점에서 끝 정점으로 가는 가중치 설정
    g->weight[end - 1][start - 1] = w; // 반대 방향도 동일하게 설정

    // 현재 그래프의 최대 정점 번호로 설정
    if (g->n < start) g->n = start;
    if (g->n < end) g->n = end;
}

// 선택되지 않은 정점 중 가장 작은 거리 값을 가진 정점 반환
int get_min_vertex(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i; // 선택되지 않고, 가장 작은 거리 값을 가진 정점 갱신
        }
    }
    return v;
}

// Prim MST 알고리즘
void FindPrimMST(GraphType* g) {
    printf("\nPrim MST Algorithm\n");
    for (int i = 0; i < g->n; i++) {
        int u = get_min_vertex(g->n); // 선택되지 않은 정점 중 최소 거리 값을 가진 정점 선택
        selected[u] = TRUE; 

        if (distance[u] == INF) return; // 도달할 수 없는 정점이면 종료

        printf("정점 %d 추가\n", u + 1);

        // 선택된 정점의 인접 정점의 거리 값 갱신
        for (int v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
            }
        }
    }
}

void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    FindPrimMST(g);

    free(g);
    return 0;
}
