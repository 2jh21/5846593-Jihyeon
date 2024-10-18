#include <stdio.h>
#include <stdlib.h>

// �迭 �� ��� ��ȯ
void swap(int inputData[], int i, int j) {
    int temp = inputData[i];
    inputData[i] = inputData[j];
    inputData[j] = temp;
}

//�ִ� �� ����
// �θ�� �۽��� ���Ͽ� ū ���� �θ�� ������ ����
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

// �ִ� �� ����
// �迭�� �ϳ��� �߰��ϸ鼭 �ִ� �� ����
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

// �� ����
// ���� ū ���� ���������� �̵���Ű�� ���� �ݺ�
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
