#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// ����� �������̽�
void runUserInterface(TreeNode* root) {
    char menu;
    element item;

    //�޴� ���
    printf("------------------------------------\n");
    printf("| i : ��� �߰�                    |\n");
    printf("| d : ��� ����                    |\n");
    printf("| p : ������ ���                  |\n");
    printf("| c : ����                         |\n");
    printf("------------------------------------\n");

    while (1) {
        //�޴� �Է¹ޱ�
        printf("\n�޴� �Է�: ");
        scanf_s(" %c", &menu, 1);

        switch (menu) {
        case 'i': //��� �߰�
            user_input_flag = 1; // ����� �Է��� ��Ÿ��
            printf("�߰��� �� �Է�: ");
            scanf_s("%d", &item.key);
            InsertMaxHeapTree(root, item);
            user_input_flag = 0; // �ʱ�ȭ
            break;

        case 'd': // ��� ����
            delet_heap(root);
            break;

        case 'p': // ������ Ʈ�� ���
            printf("Ʈ�� ������ ���\n");
            display_level(root);
            break;

        case 'c': // ���α׷� ����
            return;

        default: // �߸��� �Է� ó��
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
}

int main() {
    int inputData[] = { 90,89,70,36,75,63,65,21,18,15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = generateMaxHeapTree(inputData, size);

    runUserInterface(root);

    free(root);
    return 0;
}