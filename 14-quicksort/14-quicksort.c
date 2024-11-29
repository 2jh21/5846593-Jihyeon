#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, temp) { temp = x; x = y; y = temp; }

int sorted[SIZE];
int comparisonCount, moveCount, totalComparisons = 0, totalMoveCount = 0, isFirst = 0, rounds = 0;

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

// �迭�� Ư�� ������ ����
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;

    pivot = array[left];
    moveCount++; //pivot�� ���� ������ �̵�Ƚ�� ����

    do {
        do { // low �����͸� ���������� �̵��ϸ� �ǹ����� ū �� ã��
            low++;
            comparisonCount++; // low �����Ͱ� �迭 ������ ����� �ʰ� �ǹ����� ������ Ȯ��
        } while (low <= right && array[low] < pivot);

        do { // high �����͸� �������� �̵��ϸ� �ǹ����� ���� �� ã��
            high--;
            comparisonCount++; // high �����Ͱ� �迭 ������ ����� �ʰ� �ǹ����� ������ Ȯ��
        } while (high >= left && array[high] > pivot);


        if (low < high) {
            SWAP(array[low], array[high], temp);
            moveCount += 3; // swap�Ͽ� 3�� �̵�Ƚ�� ����
        }
    } while (low < high);

    SWAP(array[left], array[high], temp); // �ǹ��� high ��ġ�� ���� ��ȯ�Ͽ� �ǹ��� ���ĵ� ��ġ�� �̵�
    moveCount += 3;// swap�Ͽ� 3�� �̵�Ƚ�� ����

    return high;
}

// ������ (����� ���)
void doQuickSort(int array[], int left, int right) {

    // 10���帶�� ���� ���
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 40; i <= 60; i++)
            printf("%3d ", array[i]);
        printf("\n\n");
    }
    rounds++;//���� ����

    if (left < right) {
        int q = partition(array, left, right);
        doQuickSort(array, left, q - 1);
        doQuickSort(array, q + 1, right);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRoundArray(array);

        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
