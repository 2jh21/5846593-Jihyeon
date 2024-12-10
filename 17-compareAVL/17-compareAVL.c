#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compareCount, searchCount;

// 노드를 정의하는 구조체
typedef struct Node {
	int key;
	struct Node* left, * right;
	int height;
}Node;

// 새로운 노드 생성
Node* createNode(int key) {
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->right = nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}

// 메모리 해제

void freeTree(Node* root) {
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

// 노드의 높이 반환
int getHeight(Node* nptr) {
	if (nptr == (Node*)NULL)
		return 0;
	else return nptr->height;
}

//노드의 균형 계수 반환 
int getBalance(Node* nptr) {
	return getHeight(nptr->left) - getHeight(nptr->right); // 왼쪽 높이 - 오른쪽 높이
}

// 최솟값을 가진 노드 반환
Node* getMinValueNode(Node* node) {
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

// 오른쪽 회전
Node* rotateRight(Node* y) {
	Node* x = y->left;
	Node* T3 = x->right;

	x->right = y;
	y->left = T3;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

	return x;
}

// 왼쪽으로 회전
Node* rotateLeft(Node* y) {
	Node* x = y->right;
	Node* T2 = x->left;

	x->left = y;
	y->right = T2;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

	return x;
}

// AVL 트리에 키 삽입
Node* avl_insertNode(Node* root, int key) {
	// 트리가 비어있으면 새 노드 생성
	if (root == (Node*)NULL)
		return createNode(key); 

	// 삽입할 키가 현재 노드의 키보다 작으면 왼쪽으로 삽입
	if (root->key > key) 
		root->left = avl_insertNode(root->left, key);
	
	// 삽입할 키가 현재 노드의 키보다 크면 오른쪽으로 삽입
	else if (root->key < key)
		root->right = avl_insertNode(root->right, key);

	// 중복 키는 AVL 트리에 삽입되지 않음
	else
		return root;

	// 노드의 높이 업데이트
	root->height = 1 + (getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right);

	int balance = getBalance(root);

	// 불균형 해소를 위한 회전
	if (balance >= 2) {
		if (getBalance(root->left) >= 0)
			return rotateRight(root);

		else {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
	}
	else if (balance <= -2) {
		if (getBalance(root->right) < 0)
			return rotateLeft(root);

		else {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
	}
	else
		return root;
}

// AVL 트리에서 노드 삭제
Node* avl_deleteNode(Node* root, int key) {
	if (root == NULL) return root; 

	// 삭제할 키 탐색
	if (key < root->key)
		root->left = avl_deleteNode(root->left, key);
	else if (key > root->key)
		root->right = avl_deleteNode(root->right, key);
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Node* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else {
				*root = *temp;
			}
			free(temp);
		}
		else {
			Node* temp = getMinValueNode(root->right);
			root->key = temp->key;
			root->right = avl_deleteNode(root->right, temp->key);
		}
	}

	if (root == NULL) return root;

	// 높이 업데이트
	root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

	int balance = getBalance(root);

	// 불균형 해소를 위한 회전
	if (balance > 1 && getBalance(root->left) >= 0)
		return rotateRight(root);

	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return rotateLeft(root);

	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}

// 주어진 키 탐색
Node* searchNode(Node* node, int key) {
	while (node != NULL) {
		if (key == node->key) { // 키를 찾은 경우
			compareCount++; // 비교 횟수 증가
			return node;
		}
		else if (key < node->key) { // 키가 현재 노드보다 작으면 왼쪽 탐색
			compareCount++; // 비교 횟수 증가
			node = node->left;
		}
		else { 	// 키가 현재 노드보다 크면 오른쪽 탐색
			compareCount++; // 비교 횟수 증가
			node = node->right;
		}
	}
	return NULL;
}

// AVL 트리에 대한 랜덤 삽입/삭제/탐색
void doAVLBatch(Node* root) {
	for (int i = 0; i < 2000; i++) {
		int A = rand() % 3;
		int B = rand() % 1000;

		if (A == 0) {
			root = avl_insertNode(root, B);
		}
		else if (A == 1) {
			root = avl_deleteNode(root, B);
		}
		else if (A == 2) {
			searchCount++;
			searchNode(root, B);
		}
	}
}

// 이진 탐색 트리에 노드 삽입
Node* binary_insertNode(Node* node, int key) {
	// 트리가 비어 있으면 새로운 노드 생성
	if (node == NULL)
		return createNode(key);

	// 삽입할 키가 현재 노드보다 작으면 왼쪽으로 삽입
	if (key < node->key)
		node->left = binary_insertNode(node->left, key);
	// 삽입할 키가 현재 노드보다 크면 오른쪽으로 삽입
	else if (key > node->key)
		node->right = binary_insertNode(node->right, key);

	return node;
}

// 이진 탐색 트리에서 노드 삭제
Node* binary_deleteNode(Node* root, int key) {
	if (root == NULL)
		return root;

	if (key < root->key) {
		root->left = binary_deleteNode(root->left, key);
	}
	else if (key > root->key) {
		root->right = binary_deleteNode(root->right, key);
	}
	else {
		if (root->left == NULL || root->right == NULL) {
			Node* temp = root->left ? root->left : root->right;
			free(root);
			return temp;
		}

		Node* temp = getMinValueNode(root->right);
		root->key = temp->key;
		root->right = binary_deleteNode(root->right, temp->key);
	}

	return root;
}

// 이진 탐색 트리에 대한 랜덤 삽입/삭제/탐색
doBinaryBatch(Node* root) {
	searchCount = 0;

	for (int i = 0; i < 2000; i++) {
		int A = rand() % 3;
		int B = rand() % 1000;

		if (A == 0) {
			root = binary_insertNode(root, B); 
		}
		else if (A == 1) {
			root = binary_deleteNode(root, B);
		}
		else if (A == 2) {
			searchCount++;
			searchNode(root, B);
		}
	}
}


int main(int argc, char* argv[]) {
	Node* root = NULL;
	srand(time(NULL));
	float allCount = 0.0;

	doAVLBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average AVL compare count: %.2f\n", allCount);

	freeTree(root);
	root = NULL;
	compareCount = allCount = 0;

	doBinaryBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average Bin compare count: %.2f\n", allCount);
	freeTree(root);
	return 0;

}