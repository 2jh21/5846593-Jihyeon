#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int user_input_flag = 0; // 사용자 입력 플래그를 받을 수 있는 전역변수 선언

// 힙 생성
TreeNode* create_heap() {
    return (TreeNode*)malloc(sizeof(TreeNode));
}

// 힙 초기화
void init_heap(TreeNode* h) {
    h->heap_size = 0;
}

// 힙 비었는지 확인
int is_empty_heap(TreeNode* h) {
    return (h->heap_size == 0);
}

// 힙 가득 찼는지 확인
int is_full_heap(TreeNode* h, element item) {
    return (h->heap_size == (MAX_SIZE - 1));
}

// 주어진 데이터로 최대 힙 생성
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = create_heap();
    init_heap(root);
    for (int i = 0; i < size; i++) {
        element item;
        item.key = inputData[i];
        InsertMaxHeapTree(root, item);
    }
    return root;
}

// 힙에 요소 삽입(int display를 추가해 과정 출력이 필요할때만 출력)
void InsertMaxHeapTree(TreeNode* h, element item) {
    int i = ++(h->heap_size);
    h->heap[i] = item;
    int move = 0;

    if (user_input_flag) // 사용자 입력을 받았을때만 과정 출력
        display_heap(h);

    // 부모 노드와 비교하여, 부모 노드의 키가 현재 노드의 키보다 작으면 스왑
    while ((i != 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];
        h->heap[i / 2] = item;
        move++;

        if (user_input_flag) // 사용자 입력을 받았을때만 과정 출력
            display_heap(h);

        i = i / 2;
    }
    if (user_input_flag) // 사용자 입력을 받았을때만 노드 이동 횟수 출력
        printf("노드가 이동된 횟수: %d\n", move);
}

// 힙에서 루트 노드 삭제
element delet_heap(TreeNode* h) {
    int parent, child;
    element item, temp;
    int move = 0;

    item = h->heap[1];
    temp = h->heap[h->heap_size--];

    h->heap[1] = temp; 
    display_heap(h);

  
    for (parent = 1, child = 2; child <= h->heap_size; parent = child, child *= 2) {
        //자식 노드 중 더 큰 값을 가진 자식 노드를 선택
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
            child++;

        //부모 노드가 더 크거나 같다면 종료
        if (temp.key >= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        move++;
        h->heap[child] = temp;

        display_heap(h);
    }
    h->heap[parent] = temp;
    move++;
    printf("노드가 이동된 횟수: %d\n", move);

    return item;
}

// 힙의 루트 노드 찾기
element find_heap(TreeNode* h) {
    return h->heap[1];
}

// 힙 현재 상태 출력
void display_heap(TreeNode* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// 레벨별 트리 출력
void display_level(TreeNode* h) {
    int level = 1;
    int index = 1;
    int count = 1;

    while (index <= h->heap_size) {
        printf("[%d] ", level);

        for (int i = 0; i < count && index <= h->heap_size; i++, index++) {
            printf("%d ", h->heap[index].key);
        }

        printf("\n");
        count *= 2;
        level++;
    }
}

