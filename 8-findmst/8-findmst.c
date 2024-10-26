#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

// 서로소 집합 초기화
void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

// 집합 찾기
int set_find(int curr) {
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

// 두 집합 합치기
void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)
		parent[root1] = root2;
}

struct Edge {
	int start, end, weight;
};

typedef struct GraphType {
	int n;
	int v;
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화
void graph_init(GraphType* g) {
	g->n = 0;
	g->v = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// 그래프에 간선 추가
void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start; 
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;

	// 현재 그래프의 최대 정점 번호로 설정
	if (start > g->v) g->v = start;
	if (end > g->v) g->v = end;
}

// 간선을 가중치 기준으로 비교
int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// 퀵소트 기반 Kruskal 알고리즘
void QuickKruskal(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->v + 1);
	qsort(g->edges, g->n, sizeof(struct Edge), compare); // 간선 정렬

	printf("\nQuick Based Kruskal\n");

	int i = 0;
	while (edge_accepted < (g->v - 1)){ // 정점 수 -1 개의 간선 선택
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) { // 서로 다른 집합에 속하는 경우 간선 선택
			printf("Edge (%d, %d) select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

typedef struct MinHeap {
	struct Edge heap[2 * MAX_VERTICES];
	int size;
}MinHeap;

// 최소 힙 초기화
void minHeap_init(MinHeap* h) {
	h->size = 0;
}

// 최소 힙에 간선 추가
void minHeap_insert(MinHeap* h, struct Edge item) {
	int i = ++(h->size);
	while (i != 1 && item.weight < h->heap[i / 2].weight) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

// 최소 힙에서 간선 삭제
struct Edge minHeap_delete(MinHeap* h) {
	int parent = 1, child = 2;
	struct Edge item = h->heap[1];
	struct Edge temp = h->heap[(h->size)--];

	while (child <= h->size) { // 힙 재구성
		if (child < h->size && h->heap[child].weight > h->heap[child + 1].weight)
			child++;
		if (temp.weight <= h->heap[child].weight)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 최소 힙 기반 Kruskal 알고리즘
void MinHeapKruskal(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	MinHeap minHeap;
	minHeap_init(&minHeap); 

	set_init(g->v + 1);
	
	//모든 간선을 최소 힙에 삽입
	for (int i = 0; i < g->n; i++) {
		minHeap_insert(&minHeap, g->edges[i]);
	}

	printf("\nMinHeap Based Kruskal\n");

	while (edge_accepted < (g->v - 1) && minHeap.size > 0) {
		e = minHeap_delete(&minHeap);
		uset = set_find(e.start);
		vset = set_find(e.end);

		if (uset != vset) { // 서로 다른 집합에 속하면 간선 선택
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
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
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	GenerateGraph(g);

	QuickKruskal(g);
	MinHeapKruskal(g);

	free(g);
	return 0;
}
