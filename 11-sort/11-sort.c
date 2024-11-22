#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define SIZE 100

// �迭�� ���� ����
void generateRandomData(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000; // 0���� 999������ ������ �迭�� ����
}

// �迭 ���� ���
void printArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// ���� ����
void doSelectionSort(int array[]) {
    printf("Selection Sort:\n");

    int i, j, least, temp;

    for (i = 0; i < SIZE - 1; i++) {
        least = i;

        // �ּڰ��� ã�� ���� ���� ��� �˻�
        for (j = i + 1; j < SIZE; j++) {
            if (array[j] < array[least])
                least = j;
        }

        SWAP(array[i], array[least], temp); // �ּڰ��� ���ĵ��� ���� ù ��° ��ҿ� ��ȯ

        // 10�ܰ���� 20������ �߰� ��� ���
        if (i % 20 == 10) {
            printf("Step %d: ", i);
            printArray(array);
            printf("\n");
        }
    }

    printf("Step %d: ", i);
    printArray(array);
}

// ���� ����
void doInsertionSort(int array[]) {
    int n, i, j, key;
    int comparisonCount, totalComparisons = 0;

    // 20�� �ݺ��Ͽ� ��� �� Ƚ�� ���
    for (n = 0; n < 20; n++) {
        generateRandomData(array); // �迭�� �� ���� ������ ����
        comparisonCount = 0;

        //���� ���� ����
        for (i = 1; i < SIZE; i++) {
            key = array[i];
            j = i - 1;

            // key���� ū ��Ҹ� ���������� �̵�
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
                comparisonCount++; // �� Ƚ�� ����
            }
            comparisonCount++; // ������ �� Ƚ�� ����
            array[j + 1] = key;
        }

        totalComparisons += comparisonCount;
    }
 
    printf("\nInsertion Sort Compare Average: %d\n", totalComparisons / 20);
    printf("Insertion Sort Result:\n");
    printArray(array);
}

// ���� ����
void doBubbleSort(int array[]) {
    int n, i, j, temp;
    int moveCount, totalMoves = 0;

    // 20�� �ݺ��Ͽ� ��� �̵� Ƚ�� ���
    for (n = 0; n < 20; n++) {
        generateRandomData(array); // �迭�� �� ���� ������ ����
        moveCount = 0;

        //���� ���� ����
        for (i = SIZE - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (array[j] > array[j + 1]) { // ���� ��� ��
                    SWAP(array[j], array[j + 1], temp);
                    moveCount += 3; // SWAP �� �̵� 3ȸ
                }
            }
        }
        totalMoves += moveCount;
    }

    printf("\nBubble Sort Move Average: %d\n", totalMoves / 20);
    printf("Bubble Sort Result:\n");
    printArray(array);
}

int main() {
	srand(time(NULL));

	int randomData[SIZE];
	generateRandomData(randomData);

	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);

    return 0;
}