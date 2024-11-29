#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int comparisonCount, moveCount, totalComparisons = 0, totalMoves = 0, isFirst = 0, rounds;

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

// 배열 과정 출력
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

// 병합 정렬의 병합 단계
void doMerge(int array[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        comparisonCount++; // 비교횟수 증가

        if (array[i] <= array[j]) {
            sorted[k++] = array[i++]; 
            moveCount++; // 왼쪽 요소 복사 이동횟수 증가
        }
        else {
            sorted[k++] = array[j++];
            moveCount++; // 오른쪽 요소 복사 이동횟수 증가
        }
    }

    while (i <= mid) { // 왼쪽 부분 배열에 남은 요소 병합
        sorted[k++] = array[i++];
        moveCount++; // 이동횟수 증가
    }

    while (j <= right) { // 오른쪽 부분 배열에 남은 요소 병합
        sorted[k++] = array[j++];
        moveCount++; // 이동횟수 증가
    }

    for (i = left; i <= right; i++) { // 병합된 배열을 원래 배열로 복사
        array[i] = sorted[i];
        moveCount++;
    }
}

// 병합 정렬 (반복적 방법)
void doMergeSort(int array[]) {
    int left, right;
    rounds = 0;

    for (right = 1; right < SIZE; right *= 2) { // 병합 크기 증가
        for (left = 0; left < SIZE - right; left += 2 * right) { // 부분 배열 시작점 설정
            int mid = left + (right - 1); // 중간점 계산
            int end = (left + 2 * right - 1 < SIZE) ? (left + 2 * right - 1) : (SIZE - 1); // 끝점 계산

            doMerge(array, left, mid, end); // 병합 수행

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
