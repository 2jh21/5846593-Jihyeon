#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define SIZE 1000

// �迭�� ���� ����
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 10000;
}

// �迭�� Ư�� ���� ����
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        do { // low �����͸� ���������� �̵��ϸ� �ǹ����� ū �� ã��
            low++;
        } while (low <= right && list[low] < pivot);
        do {// high �����͸� �������� �̵��ϸ� �ǹ����� ���� �� ã��
            high--;
        } while (high >= left && list[high] > pivot);
        if (low < high) SWAP(list[low], list[high], temp);
    } while (low < high);

    SWAP(list[left], list[high], temp);
    return high;
}

// ������(����� ���)
void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        QuickSort(list, left, q - 1);
        QuickSort(list, q + 1, right);
    }
}

// ���� Ž���� ��� �� Ƚ�� ���
double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompareCount = 0;
    int middle, low, high;

    for (int n = 0; n < 1000; n++) {
        int compareCount = 0;
        int target = array[rand() % SIZE]; // �迭���� ���� Ÿ�� ����
        
        low = 0;
        high = SIZE - 1;

        while (low <= high) {
            int middle = (low + high) / 2; // �߰� �ε��� ���

            if (target == array[middle]) { // Ÿ�� ã���� ����
                compareCount++; // �� Ƚ�� ����
                break;
            }
            else if (target < array[middle]) { // Ÿ���� �߰������� ũ�� ������ Ž��
                compareCount++; // �� Ƚ�� ����
                high = middle - 1;
            }
            else { // Ű�� �߰������� ������ ���� Ž��
                compareCount++; // �� Ƚ�� ����
                low = middle + 1;
            }
        }

        totalCompareCount += compareCount;
    }
    return totalCompareCount / 1000.0;
}

// ���� Ž���� ��� �� Ƚ�� ���
double getAverageInterpolationSearchCompareCount(int array[]) {
    int totalCompareCount = 0;
    int middle, low, high;

    for (int n = 0; n < 1000; n++) {
        int compareCount = 0;
        int target = array[rand() % SIZE]; // �迭���� ���� Ÿ�� ����

        low = 0;
        high = SIZE - 1;

        // ���� Ž��
        while (low <= high && array[low] <= target && array[high] >= target) {
            int j = low + ((double)(target - array[low]) / (array[high] - array[low]) * (high - low)); // ���� ��ġ ���

            if (target == array[j]) {
                compareCount++; // �� Ƚ�� ����
                break;
            }
            else if (target < array[j]) {
                compareCount++; // �� Ƚ�� ����
                high = j - 1;
            }
            else {
                compareCount++; // �� Ƚ�� ����
                low = j + 1;
            }
        }

        totalCompareCount += compareCount;
    }
    return totalCompareCount / 1000.0;
}

// �迭�� ó�� 20���� ������ 20���� ��� 
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

int main() {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);

    QuickSort(array, 0, SIZE - 1);
    printArray(array);

    printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));

    printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchCompareCount(array));

    return 0;
}
