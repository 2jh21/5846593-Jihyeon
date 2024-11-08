#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "matrix.h"

int distance[MAX_VERTICES]; // ������ �ִ� �Ÿ� ����
int found[MAX_VERTICES]; // ������ �湮 ���� ����
int found_order[MAX_VERTICES]; // �湮�� ������ ���� ����
int found_index = 0;

// �׷��� �ʱ�ȭ
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

// ���� �߰�
void matrix_insert_edge(GraphMatType* g, int start, int end, int w) {
    g->weight[start - 1][end - 1] = w;
    g->weight[end - 1][start - 1] = w;
    if (g->n < start) g->n = start;
    if (g->n < end) g->n = end;
}

// �ִ� �Ÿ� ���� ����
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

// ���� ���� ���
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

// �ִ� ��� Ž�� (Dijkstra �˰���)
void matrix_shortest_path(GraphMatType* g, int start) {
    // �ʱ�ȭ
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    found_index = 0;
    found[start] = TRUE;
    distance[start] = 0;
    found_order[found_index++] = start; // ���� ���� ���� ����

    matrix_print_status(g); // �ʱ� ���� ���

    // ���� ������ ���� ����� �������� �Ÿ� ����
    for (int i = 0; i < g->n; i++) {
        if (g->weight[start][i] < INF) distance[i] = g->weight[start][i];
    }

    // ��� ������ ���� �ִ� ��� Ž��
    for (int i = 0; i < g->n - 1; i++) {
        int u = matrix_choose(distance, g->n, found); // �ִ� �Ÿ��� �ִ� ���� ����
        if (u == -1) break; // �� �̻� �湮�� ������ ���� �� ����
        found[u] = TRUE; // ���õ� ������ �湮���� ǥ��
        found_order[found_index++] = u; // �湮 ���� ����

        matrix_print_status(g); // ���� ���� ���

        // ���õ� ������ ���� �ٸ� �������� ���� �ִ� ��� ������Ʈ
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
