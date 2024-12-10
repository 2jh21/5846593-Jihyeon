#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compareCount, searchCount;

// ��带 �����ϴ� ����ü
typedef struct Node {
	int key;
	struct Node* left, * right;
	int height;
}Node;

// ���ο� ��� ����
Node* createNode(int key) {
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->right = nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}

// �޸� ����

void freeTree(Node* root) {
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

// ����� ���� ��ȯ
int getHeight(Node* nptr) {
	if (nptr == (Node*)NULL)
		return 0;
	else return nptr->height;
}

//����� ���� ��� ��ȯ 
int getBalance(Node* nptr) {
	return getHeight(nptr->left) - getHeight(nptr->right); // ���� ���� - ������ ����
}

// �ּڰ��� ���� ��� ��ȯ
Node* getMinValueNode(Node* node) {
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

// ������ ȸ��
Node* rotateRight(Node* y) {
	Node* x = y->left;
	Node* T3 = x->right;

	x->right = y;
	y->left = T3;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

	return x;
}

// �������� ȸ��
Node* rotateLeft(Node* y) {
	Node* x = y->right;
	Node* T2 = x->left;

	x->left = y;
	y->right = T2;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

	return x;
}

// AVL Ʈ���� Ű ����
Node* avl_insertNode(Node* root, int key) {
	// Ʈ���� ��������� �� ��� ����
	if (root == (Node*)NULL)
		return createNode(key); 

	// ������ Ű�� ���� ����� Ű���� ������ �������� ����
	if (root->key > key) 
		root->left = avl_insertNode(root->left, key);
	
	// ������ Ű�� ���� ����� Ű���� ũ�� ���������� ����
	else if (root->key < key)
		root->right = avl_insertNode(root->right, key);

	// �ߺ� Ű�� AVL Ʈ���� ���Ե��� ����
	else
		return root;

	// ����� ���� ������Ʈ
	root->height = 1 + (getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right);

	int balance = getBalance(root);

	// �ұ��� �ؼҸ� ���� ȸ��
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

// AVL Ʈ������ ��� ����
Node* avl_deleteNode(Node* root, int key) {
	if (root == NULL) return root; 

	// ������ Ű Ž��
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

	// ���� ������Ʈ
	root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

	int balance = getBalance(root);

	// �ұ��� �ؼҸ� ���� ȸ��
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

// �־��� Ű Ž��
Node* searchNode(Node* node, int key) {
	while (node != NULL) {
		if (key == node->key) { // Ű�� ã�� ���
			compareCount++; // �� Ƚ�� ����
			return node;
		}
		else if (key < node->key) { // Ű�� ���� ��庸�� ������ ���� Ž��
			compareCount++; // �� Ƚ�� ����
			node = node->left;
		}
		else { 	// Ű�� ���� ��庸�� ũ�� ������ Ž��
			compareCount++; // �� Ƚ�� ����
			node = node->right;
		}
	}
	return NULL;
}

// AVL Ʈ���� ���� ���� ����/����/Ž��
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

// ���� Ž�� Ʈ���� ��� ����
Node* binary_insertNode(Node* node, int key) {
	// Ʈ���� ��� ������ ���ο� ��� ����
	if (node == NULL)
		return createNode(key);

	// ������ Ű�� ���� ��庸�� ������ �������� ����
	if (key < node->key)
		node->left = binary_insertNode(node->left, key);
	// ������ Ű�� ���� ��庸�� ũ�� ���������� ����
	else if (key > node->key)
		node->right = binary_insertNode(node->right, key);

	return node;
}

// ���� Ž�� Ʈ������ ��� ����
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

// ���� Ž�� Ʈ���� ���� ���� ����/����/Ž��
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