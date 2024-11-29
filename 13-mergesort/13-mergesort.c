#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int comparisonCount, moveCount, totalComparisons = 0, totalMoves = 0, isFirst = 0, rounds;

// �迭�� ���� ���� 
void generateRoundArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000; // 0���� 999������ ������ �迭�� ����
}

// �迭 ��ü ���
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// �迭 ���� ���
void printProcess(int array[]) {
    int mid = SIZE / 2;

    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("| ");
    for (int i = mid - 1; i < mid + 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

// ���� ������ ���� �ܰ�
void doMerge(int array[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        comparisonCount++; // ��Ƚ�� ����

        if (array[i] <= array[j]) {
            sorted[k++] = array[i++]; 
            moveCount++; // ���� ��� ���� �̵�Ƚ�� ����
        }
        else {
            sorted[k++] = array[j++];
            moveCount++; // ������ ��� ���� �̵�Ƚ�� ����
        }
    }

    while (i <= mid) { // ���� �κ� �迭�� ���� ��� ����
        sorted[k++] = array[i++];
        moveCount++; // �̵�Ƚ�� ����
    }

    while (j <= right) { // ������ �κ� �迭�� ���� ��� ����
        sorted[k++] = array[j++];
        moveCount++; // �̵�Ƚ�� ����
    }

    for (i = left; i <= right; i++) { // ���յ� �迭�� ���� �迭�� ����
        array[i] = sorted[i];
        moveCount++;
    }
}

// ���� ���� (�ݺ��� ���)
void doMergeSort(int array[]) {
    int left, right;
    rounds = 0;

    for (right = 1; right < SIZE; right *= 2) { // ���� ũ�� ����
        for (left = 0; left < SIZE - right; left += 2 * right) { // �κ� �迭 ������ ����
            int mid = left + (right - 1); // �߰��� ���
            int end = (left + 2 * right - 1 < SIZE) ? (left + 2 * right - 1) : (SIZE - 1); // ���� ���

            doMerge(array, left, mid, end); // ���� ����

            rounds++;

            if (rounds % 10 == 0 && isFirst == 0) {
                printProcess(array);
            }
        }
    }
}

int main() {
    srand(time(NULL));

    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRoundArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doMergeSort(array);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
