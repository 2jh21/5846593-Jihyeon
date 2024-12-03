#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define SIZE 1000

int compareCount;

// 배열에 난수 삽입
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000;
}

// 선형 탐색의 평균 비교 횟수 계산
double getAverageLinearSearchCompareCount(int array[]) {
    int n, i, totalCompareCount = 0, target;
    for (n = 0; n < 100; n++) {
        compareCount = 0;
        target = array[rand() % SIZE]; // 배열에서 랜덤 타켓 선택

        for (i = 0; i < SIZE; i++) {
            compareCount++; // 비교 횟수 증가
            if (array[i] == target) // 타겟 찾으면 종료
                break;
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

// 배열의 특정 구간 분할
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = array[left];
    do {
        do { // low 포인터를 오른쪽으로 이동하며 피벗보다 큰 값 찾기
            low++;
            compareCount++; // 비교 횟수 증가
        } while (low <= right && array[low] < pivot);
       
        do { // high 포인터를 왼쪽으로 이동하며 피벗보다 작은 값 찾기
            high--;
            compareCount++; // 비교 횟수 증가
        } while (high >= left && array[high] > pivot);
       
        if (low < high) 
            SWAP(array[low], array[high], temp);

    } while (low < high);

    SWAP(array[left], array[high], temp);
    return high;
}

// 퀵정렬(재귀적 방법)
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        doQuickSort(list, left, q - 1);
        doQuickSort(list, q + 1, right);
    }
}

// 퀵 정렬의 총 비교 횟수 계산
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; // 비교 횟수 초기화
    doQuickSort(array, 0, SIZE - 1); // 배열 전체를 퀵정렬
}

// 이진 탐색의 평균 비교 횟수 계산
double getAverageBinarySearchCompareCount(int array[]) {
    int n, totalCompareCount = 0, target;
    int middle, low, high;

    for (n = 0; n < 100; n++) {
        compareCount = 0;
        target = array[rand() % SIZE]; // 배열에서 랜덤 타켓 선택

        low = 0;
        high = SIZE - 1;

        while (low <= high) {
            middle = (low + high) / 2; // 중간 인덱스 계산

            if (array[middle] == target) { // 타켓 찾으면 종료
                compareCount++; // 비교 횟수 증가
                break;
            }
            else if (array[middle] < target) { // 타겟이 중간값보다 크면 오른쪽 탐색
                compareCount++; // 비교 횟수 증가
                low = middle + 1;
            }
            else { // 키가 중간값보다 작으면 왼쪽 탐색
                compareCount++; // 비교 횟수 증가
                high = middle - 1;
            }
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

// 배열의 처음 20개와 마지막 20개를 출력
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
