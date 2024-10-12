#include <stdio.h>
#include <stdlib.h>

int size;

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int ltag, rtag;
}ThreadNode;

TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL)
        return new_node(key);

    if (root->data == key)
        return root;
    else if (root->data > key)
        root->left = insert_node(root->left, key);
    else
        root->right = insert_node(root->right, key);

    return root;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

ThreadNode* new_threadnode(int key) {
    ThreadNode* node = (ThreadNode*)malloc(sizeof(ThreadNode));
    node->data = key;
    node->left = node->right = NULL;
    node->ltag = node->rtag = 1;
    return node;
}

ThreadNode* insert_threadnode(ThreadNode* root, int key) {
    if (root == NULL)
        return new_threadnode(key);

    if (key < root->data) {
        if (root->ltag == 0) {
            root->left = insert_threadnode(root->left, key);
        }
        else {
            ThreadNode* newNode = new_threadnode(key);
            newNode->left = root->left;
            newNode->ltag = 1;
            newNode->right = root;
            newNode->rtag = 1;
            root->left = newNode;
            root->ltag = 0;
        }
    }
    else {
        if (root->rtag == 0) {
            root->right = insert_threadnode(root->right, key);
        }
        else {
            ThreadNode* newNode = new_threadnode(key);
            newNode->right = root->right;
            newNode->rtag = 1;
            newNode->left = root;
            newNode->ltag = 1;
            root->right = newNode;
            root->rtag = 0;
        }
    }
    return root;
}

ThreadNode* GenerateThreadTree(int inputData[]) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_threadnode(root, inputData[i]);
    }
    return root;
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;
    while (current != NULL && current->ltag == 0) {
        current = current->left;
    }

    while (current != NULL) {
        printf("%d ", current->data);
        if (current->rtag == 1) {
            current = current->right;
        }
        else {
            current = current->right;
            while (current != NULL && current->ltag == 0) {
                current = current->left;
            }
        }
    }
}

int main() {
    int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };
    size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(inputData);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);

    return 0;
}