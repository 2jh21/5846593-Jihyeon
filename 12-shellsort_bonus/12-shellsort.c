#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// �迭�� ���� ���� 
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++)
        array[i] = rand() % 1000; // 0���� 999������ ������ �迭�� ����
}

// �迭 ��ü ���
void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d ", array[i]);
    printf("\n\n");
}

// �迭 �Ϻ� ��� (���� ��¿�)
void printProcess(int array[]) {
    for (int i = 0; i < 20; i++)
        printf("%d ", array[i]);
    printf(" ... \n\n");
}

// gap��ŭ ������ ��ҵ� ���� ����
void gapInsertionSort(int array[], int first, int last, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;

    for (i = first + gap; i <= last; i = i + gap) {
        key = array[i]; 
        (*moveCount)++; // key�� �������� �̵� Ƚ�� ����
        for (j = i - gap; j >= first && key < array[j]; j = j - gap) {
            array[j + gap] = array[j]; // key���� ū ��Ҹ� ���������� �̵�
            (*comparisonCount)++; // �� Ƚ�� ����
            (*moveCount)++; // �̵� Ƚ�� ����
        }
        (*comparisonCount)++; // ������ �� Ƚ�� ����
        array[j + gap] = key;
        (*moveCount)++; // key ���� �̵� Ƚ�� ����
    }
}

// �� ����
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int totalComparisonCount = 0, totalMoveCount = 0;

    // 20�� �ݺ��Ͽ� ��� �� �� �̵� Ƚ�� ���
    for (int n = 0; n < 20; n++) { 
        generateRandomNumbers(array); // �迭�� �� ���� ������ ����
        *comparisonCount = 0; 
        *moveCount = 0;

        // ������ gapType�� ���� ���̸� ���� ����
        for (int gap = ARRAY_SIZE / gapType; gap > 0; gap = gap / gapType) {
            if (n == 0) { // ù ��° �ݺ� ���� ���
                printf("Sorting with gap = %d:\n", gap);
                for (int i = 0; i < gap; i++)
                    gapInsertionSort(array, i, ARRAY_SIZE - 1, gap, comparisonCount, moveCount);
                printProcess(array); // ���� ���� ���
            }
            else {
                for (int i = 0; i < gap; i++)
                    gapInsertionSort(array, i, ARRAY_SIZE - 1, gap, comparisonCount, moveCount);
            }
        }

        if (n == 0) { // ù ��° �ݺ� ���� ��� ���
            printf("Sorted shellArray (gap = %d):\n", gapType);
            printArray(array);
        }

        totalComparisonCount += *comparisonCount;
        totalMoveCount += *moveCount;
    }

    *comparisonCount = totalComparisonCount / 20;
    *moveCount = totalMoveCount / 20;           
}

// ���� ����
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int n, i, j, key;
    int totalComparisonCount = 0, totalMoveCount = 0;

    // 20�� �ݺ��Ͽ� ��� �� �� �̵� Ƚ�� ���
    for (n = 0; n < 20; n++) {
        generateRandomNumbers(array); // �迭�� �� ���� ������ ����
        *comparisonCount = 0;
        *moveCount = 0;

        //���� ���� ����
        for (i = 1; i < ARRAY_SIZE; i++) {
            key = array[i]; 
            (*moveCount)++; // Ű�� �������� �̵� Ƚ�� ����
            j = i - 1;
            
            // key���� ū ��Ҹ� ���������� �̵�
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
                (*comparisonCount)++; // �� Ƚ�� ����
                (*moveCount)++; // �̵� Ƚ�� ����
            }
            (*comparisonCount)++; // ������ �� Ƚ�� ����
            array[j + 1] = key; 
            (*moveCount)++; // Ű ���� �̵� Ƚ�� ����
        }

        if (n == 0) { // ù ��° �ݺ� ���� ��� ���
            printf("Sorted insertionArray:\n");
            printArray(array);
        }

        totalComparisonCount += *comparisonCount;
        totalMoveCount += *moveCount;
    }

    *comparisonCount = totalComparisonCount / 20;
    *moveCount = totalMoveCount / 20;
}

int main() {
    srand(time(NULL));

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array);

    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
