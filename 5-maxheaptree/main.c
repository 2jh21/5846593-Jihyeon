#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// 사용자 인터페이스
void runUserInterface(TreeNode* root) {
    char menu;
    element item;

    //메뉴 출력
    printf("------------------------------------\n");
    printf("| i : 노드 추가                    |\n");
    printf("| d : 노드 삭제                    |\n");
    printf("| p : 레벨별 출력                  |\n");
    printf("| c : 종료                         |\n");
    printf("------------------------------------\n");

    while (1) {
        //메뉴 입력받기
        printf("\n메뉴 입력: ");
        scanf_s(" %c", &menu, 1);

        switch (menu) {
        case 'i': //노드 추가
            user_input_flag = 1; // 사용자 입력을 나타냄
            printf("추가할 값 입력: ");
            scanf_s("%d", &item.key);
            InsertMaxHeapTree(root, item);
            user_input_flag = 0; // 초기화
            break;

        case 'd': // 노드 삭제
            delet_heap(root);
            break;

        case 'p': // 레벨별 트리 출력
            printf("트리 레벨별 출력\n");
            display_level(root);
            break;

        case 'c': // 프로그램 종료
            return;

        default: // 잘못된 입력 처리
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
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