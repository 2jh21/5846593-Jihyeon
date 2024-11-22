#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define SIZE 100

// 배열에 난수 삽입
void generateRandomData(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000; // 0부터 999까지의 난수를 배열에 삽입
}

// 배열 내용 출력
void printArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// 선택 정렬
void doSelectionSort(int array[]) {
    printf("Selection Sort:\n");

    int i, j, least, temp;

    for (i = 0; i < SIZE - 1; i++) {
        least = i;

        // 최솟갑을 찾기 위해 남은 요소 검사
        for (j = i + 1; j < SIZE; j++) {
            if (array[j] < array[least])
                least = j;
        }

        SWAP(array[i], array[least], temp); // 최솟값을 정렬되지 않은 첫 번째 요소와 교환

        // 10단계부터 20단위로 중간 결과 출력
        if (i % 20 == 10) {
            printf("Step %d: ", i);
            printArray(array);
            printf("\n");
        }
    }

    printf("Step %d: ", i);
    printArray(array);
}

// 삽입 정렬
void doInsertionSort(int array[]) {
    int n, i, j, key;
    int comparisonCount, totalComparisons = 0;

    // 20번 반복하여 평균 비교 횟수 계산
    for (n = 0; n < 20; n++) {
        generateRandomData(array); // 배열에 새 랜덤 데이터 생성
        comparisonCount = 0;

        //삽입 정렬 수행
        for (i = 1; i < SIZE; i++) {
            key = array[i];
            j = i - 1;

            // key보다 큰 요소를 오른쪽으로 이동
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
                comparisonCount++; // 비교 횟수 증가
            }
            comparisonCount++; // 마지막 비교 횟수 증가
            array[j + 1] = key;
        }

        totalComparisons += comparisonCount;
    }
 
    printf("\nInsertion Sort Compare Average: %d\n", totalComparisons / 20);
    printf("Insertion Sort Result:\n");
    printArray(array);
}

// 버블 정렬
void doBubbleSort(int array[]) {
    int n, i, j, temp;
    int moveCount, totalMoves = 0;

    // 20번 반복하여 평균 이동 횟수 계산
    for (n = 0; n < 20; n++) {
        generateRandomData(array); // 배열에 새 랜덤 데이터 생성
        moveCount = 0;

        //버블 정렬 수행
        for (i = SIZE - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (array[j] > array[j + 1]) { // 인접 요소 비교
                    SWAP(array[j], array[j + 1], temp);
                    moveCount += 3; // SWAP 시 이동 3회
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