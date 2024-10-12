#include <stdio.h>
#include <stdlib.h>

#define SIZE 15

typedef int value;

typedef struct TreeNode {
    value data;
    struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;

typedef struct StackNode {
    element data;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) {
    s->top = NULL;
}

int is_empty(LinkedStackType* s) {
    return (s->top == NULL);
}

int is_full(LinkedStackType* s) {
    return 0;
}

void push(LinkedStackType* s, element item) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    if (temp == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

element pop(LinkedStackType* s) {
    if (is_empty(s)) {
        printf("스택이 비어 있습니다.\n");
        return NULL;
    }
    StackNode* temp = s->top;
    element data = temp->data;
    s->top = temp->link;
    free(temp);
    return data;
}

void print_stack(LinkedStackType* s) {
    for (StackNode* p = s->top; p != NULL; p = p->link)
        printf("%d->", p->data->data);
    printf("NULL \n");
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            printf("visit(%d)\n", nptr->data);
            push(&s, nptr);
            printf("push(%d)", nptr->data);
            nptr = nptr->left;
        }
        nptr = pop(&s);
        printf("pop(%d)", nptr->data);
        nptr = nptr->right;
    }
    printf("\n");
}

void LinkInOrder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            printf("push(%d)", nptr->data);
            nptr = nptr->left;
        }
        nptr = pop(&s);
        printf("pop(%d)", nptr->data);
        if (nptr != NULL) {
            printf("visit(%d)\n", nptr->data);
            nptr = nptr->right;
        }
    }
}

void LinkPostOrder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* lastVisited = NULL;
    TreeNode* nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        if (nptr != NULL) {
            push(&s, nptr);
            printf("push(%d)", nptr->data);
            nptr = nptr->left;
        }
        else {
            TreeNode* peekNode = s.top->data;
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                nptr = peekNode->right;
            }
            else {
                printf("visit(%d)\n", peekNode->data);
                lastVisited = pop(&s);
                printf("pop(%d)", lastVisited->data);
            }
        }
    }
    printf("\n");
}

void LinkOrders(TreeNode* root) {
    printf("\n전위 순회\n");
    LinkPreOrder(root);
    printf("\n중위 순회\n");
    LinkInOrder(root);
    printf("\n후위 순회\n");
    LinkPostOrder(root);
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateLinkTree(root);
    
    LinkOrders(root);

    return 0;
}
