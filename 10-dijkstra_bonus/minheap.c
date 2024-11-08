#include <stdio.h>
#include <stdlib.h>

#include "minheap.h"

// ���ο� �ּ� �� ��� ����
MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->vertex = v;
    minHeapNode->distance = dist;
    return minHeapNode;
}

// �ּ� �� ����
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// �� ��� ��ȯ
void swap(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// �� �籸�� 
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // ���� �ڽ��� �� ���� ��� smallest ������Ʈ
    if (left < minHeap->size &&
        minHeap->array[left]->distance < minHeap->array[smallest]->distance)
        smallest = left;

    // ������ �ڽ��� �� ���� ��� smallest ������Ʈ
    if (right < minHeap->size &&
        minHeap->array[right]->distance < minHeap->array[smallest]->distance)
        smallest = right;

    // smallest�� ���� �ε����� �ƴ� ���, �� �Ӽ��� �����ϹǷ� ��ȯ
    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        swap(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// �ּ� �Ÿ� ���� ����
MinHeapNode* removeMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return NULL;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// �Ÿ� ������Ʈ
void updateDistance(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->distance = dist;

    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

// Ư�� ������ ���� ���� �����ϴ� Ȯ��
int isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}
