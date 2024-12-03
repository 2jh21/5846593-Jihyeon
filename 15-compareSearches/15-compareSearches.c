#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define SIZE 1000

int compareCount;

// �迭�� ���� ����
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000;
}

// ���� Ž���� ��� �� Ƚ�� ���
double getAverageLinearSearchCompareCount(int array[]) {
    int n, i, totalCompareCount = 0, target;
    for (n = 0; n < 100; n++) {
        compareCount = 0;
        target = array[rand() % SIZE]; // �迭���� ���� Ÿ�� ����

        for (i = 0; i < SIZE; i++) {
            compareCount++; // �� Ƚ�� ����
            if (array[i] == target) // Ÿ�� ã���� ����
                break;
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

// �迭�� Ư�� ���� ����
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = array[left];
    do {
        do { // low �����͸� ���������� �̵��ϸ� �ǹ����� ū �� ã��
            low++;
            compareCount++; // �� Ƚ�� ����
        } while (low <= right && array[low] < pivot);
       
        do { // high �����͸� �������� �̵��ϸ� �ǹ����� ���� �� ã��
            high--;
            compareCount++; // �� Ƚ�� ����
        } while (high >= left && array[high] > pivot);
       
        if (low < high) 
            SWAP(array[low], array[high], temp);

    } while (low < high);

    SWAP(array[left], array[high], temp);
    return high;
}

// ������(����� ���)
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        doQuickSort(list, left, q - 1);
        doQuickSort(list, q + 1, right);
    }
}

// �� ������ �� �� Ƚ�� ���
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; // �� Ƚ�� �ʱ�ȭ
    doQuickSort(array, 0, SIZE - 1); // �迭 ��ü�� ������
}

// ���� Ž���� ��� �� Ƚ�� ���
double getAverageBinarySearchCompareCount(int array[]) {
    int n, totalCompareCount = 0, target;
    int middle, low, high;

    for (n = 0; n < 100; n++) {
        compareCount = 0;
        target = array[rand() % SIZE]; // �迭���� ���� Ÿ�� ����

        low = 0;
        high = SIZE - 1;

        while (low <= high) {
            middle = (low + high) / 2; // �߰� �ε��� ���

            if (array[middle] == target) { // Ÿ�� ã���� ����
                compareCount++; // �� Ƚ�� ����
                break;
            }
            else if (array[middle] < target) { // Ÿ���� �߰������� ũ�� ������ Ž��
                compareCount++; // �� Ƚ�� ����
                low = middle + 1;
            }
            else { // Ű�� �߰������� ������ ���� Ž��
                compareCount++; // �� Ƚ�� ����
                high = middle - 1;
            }
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

// �迭�� ó�� 20���� ������ 20���� ���
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]); 
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    printf("Average Linear Search Compare Count: %.2f\n", getAverageLinearSearchCompareCount(array));

    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    printf("Average Binary Search Compare Count: %.2f\n", getAverageBinarySearchCompareCount(array));

    printArray(array);

    return 0;
}
