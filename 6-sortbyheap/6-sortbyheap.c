#include <stdio.h>
#include <stdlib.h>

// 배열 두 요소 교환
void swap(int inputData[], int i, int j) {
    int temp = inputData[i];
    inputData[i] = inputData[j];
    inputData[j] = temp;
}

//최대 힙 유지
// 부모와 작식을 비교하여 큰 값이 부모로 오도록 조정
void resortHeap(int inputData[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    if (largest != i) {
        swap(inputData, i, largest);
        resortHeap(inputData, n, largest);
    }
}

// 최대 힙 생성
// 배열을 하나씩 추가하면서 최대 힙 생성
void BuildMaxHeap(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        int current = i;
        while (current > 0 && inputData[(current - 1) / 2] < inputData[current]) {
            swap(inputData, (current - 1) / 2, current);
            current = (current - 1) / 2;
        }

        for (int k = 0; k <= i; k++) {
            printf("%d ", inputData[k]);
        }
        printf("\n");
    }
}

// 힙 정렬
// 가장 큰 값을 마지막으로 이동시키고 정렬 반복
void BuildMaxHeapSort(int inputData[], int n) {
    BuildMaxHeap(inputData, n);

    for (int i = n - 1; i > 0; i--) {
        swap(inputData, 0, i);
        resortHeap(inputData, i, 0);

        for (int k = 0; k < i; k++) {
            printf("%d ", inputData[k]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    printf("<Sort>\n");
    BuildMaxHeapSort(inputData, size);

    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
