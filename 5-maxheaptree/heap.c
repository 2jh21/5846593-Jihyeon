#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int user_input_flag = 0; // ����� �Է� �÷��׸� ���� �� �ִ� �������� ����

// �� ����
TreeNode* create_heap() {
    return (TreeNode*)malloc(sizeof(TreeNode));
}

// �� �ʱ�ȭ
void init_heap(TreeNode* h) {
    h->heap_size = 0;
}

// �� ������� Ȯ��
int is_empty_heap(TreeNode* h) {
    return (h->heap_size == 0);
}

// �� ���� á���� Ȯ��
int is_full_heap(TreeNode* h, element item) {
    return (h->heap_size == (MAX_SIZE - 1));
}

// �־��� �����ͷ� �ִ� �� ����
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

// ���� ��� ����(int display�� �߰��� ���� ����� �ʿ��Ҷ��� ���)
void InsertMaxHeapTree(TreeNode* h, element item) {
    int i = ++(h->heap_size);
    h->heap[i] = item;
    int move = 0;

    if (user_input_flag) // ����� �Է��� �޾������� ���� ���
        display_heap(h);

    // �θ� ���� ���Ͽ�, �θ� ����� Ű�� ���� ����� Ű���� ������ ����
    while ((i != 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];
        h->heap[i / 2] = item;
        move++;

        if (user_input_flag) // ����� �Է��� �޾������� ���� ���
            display_heap(h);

        i = i / 2;
    }
    if (user_input_flag) // ����� �Է��� �޾������� ��� �̵� Ƚ�� ���
        printf("��尡 �̵��� Ƚ��: %d\n", move);
}

// ������ ��Ʈ ��� ����
element delet_heap(TreeNode* h) {
    int parent, child;
    element item, temp;
    int move = 0;

    item = h->heap[1];
    temp = h->heap[h->heap_size--];

    h->heap[1] = temp; 
    display_heap(h);

  
    for (parent = 1, child = 2; child <= h->heap_size; parent = child, child *= 2) {
        //�ڽ� ��� �� �� ū ���� ���� �ڽ� ��带 ����
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
            child++;

        //�θ� ��尡 �� ũ�ų� ���ٸ� ����
        if (temp.key >= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        move++;
        h->heap[child] = temp;

        display_heap(h);
    }
    h->heap[parent] = temp;
    move++;
    printf("��尡 �̵��� Ƚ��: %d\n", move);

    return item;
}

// ���� ��Ʈ ��� ã��
element find_heap(TreeNode* h) {
    return h->heap[1];
}

// �� ���� ���� ���
void display_heap(TreeNode* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// ������ Ʈ�� ���
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

