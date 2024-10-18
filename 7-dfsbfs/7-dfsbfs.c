#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICCES 100

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICCES][MAX_VERTICCES];
} GraphType;

int visited[MAX_VERTICCES];

// 그래프 생성
GraphType* create() {
    return (GraphType*)malloc(sizeof(GraphType));
}

// 그래프 초기화
void init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICCES; i++) {
        for (int j = 0; j < MAX_VERTICCES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// 정점 삽입
void insert_vertex(GraphType* g, int v) {
    if ((g->n) >= (MAX_VERTICCES - 1)) {
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

// 간선 삽입
void insert_edge(GraphType* g, int s, int e) {
    if (s >= g->n || e >= g->n) {
        fprintf(stderr, "vertex number error\n");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// 그래프 제거
void destroy(GraphType* g) {
    free(g);
}

// 깊이 우선 탐색 함수 (DFS)
// 스택을 사용하여 시작 정점부터 목표 정점까지 탐색
int dfs_search(GraphType* g, int start, int target) {
    int stack[MAX_VERTICCES];
    int top = -1;
    int visited_count = 0;
    bool found = false;
    int visit_depth[MAX_VERTICCES] = { 0 };

    memset(visited, FALSE, sizeof(visited));

    stack[++top] = start;

    while (top != -1) { // 스택이 빌 때까지 반복
        int v = stack[top--];

        if (visit_depth[v] >= 2) {
            continue;
        }

        visit_depth[v]++;
        visited_count++;
        printf("%d ", v);

        // 목표 정점을 찾으면 출력 후 종료
        if (v == target && !found) { 
            printf("\n탐색 성공: %d\n", target);
            found = true;
            return visited_count;
        }

        // 인접한 정점 중 방문하지 않은 정점을 스택에 push
        for (int i = g->n - 1; i >= 0; i--) { 
            if (g->adj_mat[v][i] && visit_depth[i] < 2) {
                stack[++top] = i;
            }
        }
    }

    // 목표 정점을 찾지 못한 경우 
    if (!found) {
        printf("\n탐색 실패: %d\n", target);
    }
    return visited_count;
}

// 너비 우선 탐색 함수 (BFS)
// 큐를 사용하여 시작 정점부터 목표 정점까지 탐색
int bfs_search(GraphType* g, int start, int target) {
    int queue[MAX_VERTICCES], front = 0, rear = 0;
    int visited_count = 0;
    bool found = false;

    memset(visited, FALSE, sizeof(visited)); // 방문 배열 초기화

    queue[rear++] = start;
    visited[start] = TRUE;

    // 큐가 빌 때까지 반복
    while (front < rear) {
        int v = queue[front++];
        if (v != start) {
            visited_count++;
        }
        printf("%d ", v);

        // 목표 정점을 찾으면 출력 후 종료
        if (v == target && !found) {
            printf("\n탐색 성공: %d\n", target);
            found = true;
            return visited_count;
        }

        // 인접한 정점 중 방문하지 않은 정점을 큐에 enqueue
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = TRUE;
            }
        }
    }

    // 목표 정점을 찾지 못한 경우
    if (!found) {
        printf("\n탐색 실패: %d\n", target);
    }
    return visited_count;
}

// 그래프 생성
void GenerateGraph(GraphType* g) {
    init(g);
    for (int i = 0; i < 11; i++) insert_vertex(g, i);

    insert_edge(g, 0, 2);
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);
    insert_edge(g, 1, 4);
    insert_edge(g, 1, 5);
    insert_edge(g, 1, 7);
    insert_edge(g, 1, 10);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 6);
    insert_edge(g, 4, 7);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);
    insert_edge(g, 8, 10);
}

// 메뉴 출력 함수
void print_menu() {
    printf("\n---------------------------------\n");
    printf(" 1\t: 깊이 우선 탐색\t|\n");
    printf(" 2\t: 너비 우선 탐색\t|\n");
    printf(" 3\t: 종료\t\t\t|\n");
    printf("---------------------------------\n");
}

int main() {
    GraphType* g = create();
    GenerateGraph(g);

    int choice;
    int start_vertex, target_vertex;

    print_menu();

    while (1) {

        printf("\n메뉴 입력: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            memset(visited, FALSE, sizeof(visited));
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start_vertex, &target_vertex);
            int dfs_count = dfs_search(g, start_vertex, target_vertex);
            printf("방문한 노드의 수: %d\n", dfs_count);
            break;
        case 2:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start_vertex, &target_vertex);
            int bfs_count = bfs_search(g, start_vertex, target_vertex);
            printf("방문한 노드의 수: %d\n", bfs_count);
            break;
        case 3:
            destroy(g);
            return 0;
        default:
            printf("잘못된 입력입니다.\n");
            break;
        }
    }
}