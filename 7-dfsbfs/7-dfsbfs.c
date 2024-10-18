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

// �׷��� ����
GraphType* create() {
    return (GraphType*)malloc(sizeof(GraphType));
}

// �׷��� �ʱ�ȭ
void init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICCES; i++) {
        for (int j = 0; j < MAX_VERTICCES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// ���� ����
void insert_vertex(GraphType* g, int v) {
    if ((g->n) >= (MAX_VERTICCES - 1)) {
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

// ���� ����
void insert_edge(GraphType* g, int s, int e) {
    if (s >= g->n || e >= g->n) {
        fprintf(stderr, "vertex number error\n");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// �׷��� ����
void destroy(GraphType* g) {
    free(g);
}

// ���� �켱 Ž�� �Լ� (DFS)
// ������ ����Ͽ� ���� �������� ��ǥ �������� Ž��
int dfs_search(GraphType* g, int start, int target) {
    int stack[MAX_VERTICCES];
    int top = -1;
    int visited_count = 0;
    bool found = false;
    int visit_depth[MAX_VERTICCES] = { 0 };

    memset(visited, FALSE, sizeof(visited));

    stack[++top] = start;

    while (top != -1) { // ������ �� ������ �ݺ�
        int v = stack[top--];

        if (visit_depth[v] >= 2) {
            continue;
        }

        visit_depth[v]++;
        visited_count++;
        printf("%d ", v);

        // ��ǥ ������ ã���� ��� �� ����
        if (v == target && !found) { 
            printf("\nŽ�� ����: %d\n", target);
            found = true;
            return visited_count;
        }

        // ������ ���� �� �湮���� ���� ������ ���ÿ� push
        for (int i = g->n - 1; i >= 0; i--) { 
            if (g->adj_mat[v][i] && visit_depth[i] < 2) {
                stack[++top] = i;
            }
        }
    }

    // ��ǥ ������ ã�� ���� ��� 
    if (!found) {
        printf("\nŽ�� ����: %d\n", target);
    }
    return visited_count;
}

// �ʺ� �켱 Ž�� �Լ� (BFS)
// ť�� ����Ͽ� ���� �������� ��ǥ �������� Ž��
int bfs_search(GraphType* g, int start, int target) {
    int queue[MAX_VERTICCES], front = 0, rear = 0;
    int visited_count = 0;
    bool found = false;

    memset(visited, FALSE, sizeof(visited)); // �湮 �迭 �ʱ�ȭ

    queue[rear++] = start;
    visited[start] = TRUE;

    // ť�� �� ������ �ݺ�
    while (front < rear) {
        int v = queue[front++];
        if (v != start) {
            visited_count++;
        }
        printf("%d ", v);

        // ��ǥ ������ ã���� ��� �� ����
        if (v == target && !found) {
            printf("\nŽ�� ����: %d\n", target);
            found = true;
            return visited_count;
        }

        // ������ ���� �� �湮���� ���� ������ ť�� enqueue
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = TRUE;
            }
        }
    }

    // ��ǥ ������ ã�� ���� ���
    if (!found) {
        printf("\nŽ�� ����: %d\n", target);
    }
    return visited_count;
}

// �׷��� ����
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

// �޴� ��� �Լ�
void print_menu() {
    printf("\n---------------------------------\n");
    printf(" 1\t: ���� �켱 Ž��\t|\n");
    printf(" 2\t: �ʺ� �켱 Ž��\t|\n");
    printf(" 3\t: ����\t\t\t|\n");
    printf("---------------------------------\n");
}

int main() {
    GraphType* g = create();
    GenerateGraph(g);

    int choice;
    int start_vertex, target_vertex;

    print_menu();

    while (1) {

        printf("\n�޴� �Է�: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            memset(visited, FALSE, sizeof(visited));
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start_vertex, &target_vertex);
            int dfs_count = dfs_search(g, start_vertex, target_vertex);
            printf("�湮�� ����� ��: %d\n", dfs_count);
            break;
        case 2:
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start_vertex, &target_vertex);
            int bfs_count = bfs_search(g, start_vertex, target_vertex);
            printf("�湮�� ����� ��: %d\n", bfs_count);
            break;
        case 3:
            destroy(g);
            return 0;
        default:
            printf("�߸��� �Է��Դϴ�.\n");
            break;
        }
    }
}