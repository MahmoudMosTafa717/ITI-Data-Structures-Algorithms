#include <iostream>
using namespace std;

// Swap two values using pointers
void swapValues(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function
void heapify(int *arr, int n, int i) {

    int largest = i;          // Assume root is the largest
    int left = 2 * i + 1;     // Left child
    int right = 2 * i + 2;    // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than the current largest
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not the root, swap and continue heapifying
    if (largest != i) {
        swapValues(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int *arr, int n) {

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one
    for (int i = n - 1; i >= 0; i--) {
        swapValues(&arr[0], &arr[i]); // Move current root (max) to end
        heapify(arr, i, 0);           // Heapify reduced heap
    }
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) cout << arr[i] << ' ';
    cout << '\n';
}

int main() {
    int numbers[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(numbers) / sizeof(numbers[0]);

    cout << "Before HeapSort: ";
    printArray(numbers, n);

    heapSort(numbers, n);

    cout << "After HeapSort: ";
    printArray(numbers, n);
    return 0;
}
