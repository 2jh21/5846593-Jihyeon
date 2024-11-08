#pragma once

typedef struct MinHeapNode {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int* pos;
    MinHeapNode** array;
} MinHeap;

MinHeapNode* newMinHeapNode(int v, int dist);
MinHeap* createMinHeap(int capacity);
void swap(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
MinHeapNode* removeMin(MinHeap* minHeap);
void updateDistance(MinHeap* minHeap, int v, int dist);
int isInMinHeap(MinHeap* minHeap, int v);
