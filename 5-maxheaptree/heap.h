#pragma once
#define MAX_SIZE 100

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} TreeNode;

extern int user_input_flag;
extern TreeNode* create_heap();
extern void init_heap(TreeNode* h);
extern int is_empty_heap(TreeNode* h);
extern int is_full_heap(TreeNode* h, element item);
extern TreeNode* generateMaxHeapTree(int inputData[], int size);
extern void InsertMaxHeapTree(TreeNode* h, element item);
extern element delet_heap(TreeNode* h);
extern element find_heap(TreeNode* h);
extern void display_heap(TreeNode* h);
extern void display_level(TreeNode* h);
extern void runUserInterface(TreeNode* root);
