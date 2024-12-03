#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define SIZE 1000

// 배열에 난수 삽입
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 10000;
}

// 배열의 특정 구간 분할
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        do { // low 포인터를 오른쪽으로 이동하며 피벗보다 큰 값 찾기
            low++;
        } while (low <= right && list[low] < pivot);
        do {// high 포인터를 왼쪽으로 이동하며 피벗보다 작은 값 찾기
            high--;
        } while (high >= left && list[high] > pivot);
        if (low < high) SWAP(list[low], list[high], temp);
    } while (low < high);

    SWAP(list[left], list[high], temp);
    return high;
}

// 퀵정렬(재귀적 방법)
void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        QuickSort(list, left, q - 1);
        QuickSort(list, q + 1, right);
    }
}

// 이진 탐색의 평균 비교 횟수 계산
double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompareCount = 0;
    int middle, low, high;

    for (int n = 0; n < 1000; n++) {
        int compareCount = 0;
        int target = array[rand() % SIZE]; // 배열에서 랜덤 타켓 선택
        
        low = 0;
        high = SIZE - 1;

        while (low <= high) {
            int middle = (low + high) / 2; // 중간 인덱스 계산

            if (target == array[middle]) { // 타켓 찾으면 종료
                compareCount++; // 비교 횟수 증가
                break;
            }
            else if (target < array[middle]) { // 타겟이 중간값보다 크면 오른쪽 탐색
                compareCount++; // 비교 횟수 증가
                high = middle - 1;
            }
            else { // 키가 중간값보다 작으면 왼쪽 탐색
                compareCount++; // 비교 횟수 증가
                low = middle + 1;
            }
        }

        totalCompareCount += compareCount;
    }
    return totalCompareCount / 1000.0;
}

// 보간 탐색의 평균 비교 횟수 계산
double getAverageInterpolationSearchCompareCount(int array[]) {
    int totalCompareCount = 0;
    int middle, low, high;

    for (int n = 0; n < 1000; n++) {
        int compareCount = 0;
        int target = array[rand() % SIZE]; // 배열에서 랜덤 타켓 선택

        low = 0;
        high = SIZE - 1;

        // 보간 탐색
        while (low <= high && array[low] <= target && array[high] >= target) {
            int j = low + ((double)(target - array[low]) / (array[high] - array[low]) * (high - low)); // 보간 위치 계산

            if (target == array[j]) {
                compareCount++; // 비교 횟수 증가
                break;
            }
            else if (target < array[j]) {
                compareCount++; // 비교 횟수 증가
                high = j - 1;
            }
            else {
                compareCount++; // 비교 횟수 증가
                low = j + 1;
            }
        }

        totalCompareCount += compareCount;
    }
    return totalCompareCount / 1000.0;
}

// 배열의 처음 20개와 마지막 20개를 출력 
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
