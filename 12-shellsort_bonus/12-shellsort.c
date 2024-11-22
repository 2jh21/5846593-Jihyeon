#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// 배열에 난수 삽입 
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++)
        array[i] = rand() % 1000; // 0부터 999까지의 난수를 배열에 삽입
}

// 배열 전체 출력
void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d ", array[i]);
    printf("\n\n");
}

// 배열 일부 출력 (과정 출력용)
void printProcess(int array[]) {
    for (int i = 0; i < 20; i++)
        printf("%d ", array[i]);
    printf(" ... \n\n");
}

// gap만큼 떨어진 요소들 삽입 정렬
void gapInsertionSort(int array[], int first, int last, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;

    for (i = first + gap; i <= last; i = i + gap) {
        key = array[i]; 
        (*moveCount)++; // key를 가져오는 이동 횟수 증가
        for (j = i - gap; j >= first && key < array[j]; j = j - gap) {
            array[j + gap] = array[j]; // key보다 큰 요소를 오른쪽으로 이동
            (*comparisonCount)++; // 비교 횟수 증가
            (*moveCount)++; // 이동 횟수 증가
        }
        (*comparisonCount)++; // 마지막 비교 횟수 증가
        array[j + gap] = key;
        (*moveCount)++; // key 삽입 이동 횟수 증가
    }
}

// 쉘 정렬
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int totalComparisonCount = 0, totalMoveCount = 0;

    // 20번 반복하여 평균 비교 및 이동 횟수 계산
    for (int n = 0; n < 20; n++) { 
        generateRandomNumbers(array); // 배열에 새 랜덤 데이터 생성
        *comparisonCount = 0; 
        *moveCount = 0;

        // 간격을 gapType에 따라 줄이며 정렬 수행
        for (int gap = ARRAY_SIZE / gapType; gap > 0; gap = gap / gapType) {
            if (n == 0) { // 첫 번째 반복 과정 출력
                printf("Sorting with gap = %d:\n", gap);
                for (int i = 0; i < gap; i++)
                    gapInsertionSort(array, i, ARRAY_SIZE - 1, gap, comparisonCount, moveCount);
                printProcess(array); // 정렬 과정 출력
            }
            else {
                for (int i = 0; i < gap; i++)
                    gapInsertionSort(array, i, ARRAY_SIZE - 1, gap, comparisonCount, moveCount);
            }
        }

        if (n == 0) { // 첫 번째 반복 최종 결과 출력
            printf("Sorted shellArray (gap = %d):\n", gapType);
            printArray(array);
        }

        totalComparisonCount += *comparisonCount;
        totalMoveCount += *moveCount;
    }

    *comparisonCount = totalComparisonCount / 20;
    *moveCount = totalMoveCount / 20;           
}

// 삽입 정렬
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int n, i, j, key;
    int totalComparisonCount = 0, totalMoveCount = 0;

    // 20번 반복하여 평균 비교 및 이동 횟수 계산
    for (n = 0; n < 20; n++) {
        generateRandomNumbers(array); // 배열에 새 랜덤 데이터 생성
        *comparisonCount = 0;
        *moveCount = 0;

        //삽입 정렬 수행
        for (i = 1; i < ARRAY_SIZE; i++) {
            key = array[i]; 
            (*moveCount)++; // 키를 가져오는 이동 횟수 증가
            j = i - 1;
            
            // key보다 큰 요소를 오른쪽으로 이동
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
                (*comparisonCount)++; // 비교 횟수 증가
                (*moveCount)++; // 이동 횟수 증가
            }
            (*comparisonCount)++; // 마지막 비교 횟수 증가
            array[j + 1] = key; 
            (*moveCount)++; // 키 삽입 이동 횟수 증가
        }

        if (n == 0) { // 첫 번째 반복 최종 결과 출력
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
