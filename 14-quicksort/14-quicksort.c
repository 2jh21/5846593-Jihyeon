#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, temp) { temp = x; x = y; y = temp; }

int sorted[SIZE];
int comparisonCount, moveCount, totalComparisons = 0, totalMoveCount = 0, isFirst = 0, rounds = 0;

// 배열에 난수 삽입 
void generateRoundArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000; // 0부터 999까지의 난수를 배열에 삽입
}

// 배열 전체 출력
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// 배열의 특정 구간을 분할
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;

    pivot = array[left];
    moveCount++; //pivot에 값을 저장한 이동횟수 증가

    do {
        do { // low 포인터를 오른쪽으로 이동하며 피벗보다 큰 값 찾기
            low++;
            comparisonCount++; // low 포인터가 배열 범위를 벗어나지 않고 피벗보다 작은지 확인
        } while (low <= right && array[low] < pivot);

        do { // high 포인터를 왼쪽으로 이동하며 피벗보다 작은 값 찾기
            high--;
            comparisonCount++; // high 포인터가 배열 범위를 벗어나지 않고 피벗보다 작은지 확인
        } while (high >= left && array[high] > pivot);


        if (low < high) {
            SWAP(array[low], array[high], temp);
            moveCount += 3; // swap하여 3번 이동횟수 증가
        }
    } while (low < high);

    SWAP(array[left], array[high], temp); // 피벗과 high 위치의 값을 교환하여 피벗을 정렬된 위치로 이동
    moveCount += 3;// swap하여 3번 이동횟수 증가

    return high;
}

// 퀵정렬 (재귀적 방법)
void doQuickSort(int array[], int left, int right) {

    // 10라운드마다 과정 출력
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 40; i <= 60; i++)
            printf("%3d ", array[i]);
        printf("\n\n");
    }
    rounds++;//라운드 증가

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
