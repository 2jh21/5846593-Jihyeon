#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 생성 함수
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
    h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;  // 새로운 노드를 삽입
}

// 삭제 함수
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;
        if (temp.key < h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 이진 트리 제거 함수
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 단말 노드 확인 함수
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 코드를 출력하는 함수
void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// 허프만 코드 출력 함수
void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }

    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }

    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

// 허프만 트리 생성 함수 (루트 노드 반환)
TreeNode* buildHuffmanTree(char ch_list[], int freq[], int n) {
    int i;
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2;

    heap = create();
    init(heap);

    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);
        for (int k = 1; k <= heap->heap_size; k++)
            printf("%d ", heap->heap[k].key);
        printf("\n");
    }

    for (i = 1; i < n; i++) {
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("// %d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
        for (int k = 1; k <= heap->heap_size; k++)
            printf("%d ", heap->heap[k].key);
        printf("\n");
    }

    e = delete_min_heap(heap);  // 최종 트리
    TreeNode* root = e.ptree;   // 루트 노드를 반환
    free(heap);
    return root;
}

// 허프만 코드 생성 및 출력 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);
    int codes[100], top = 0;
    print_codes(root, codes, top);
    destroy_tree(root);
}

int main(void) {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}
