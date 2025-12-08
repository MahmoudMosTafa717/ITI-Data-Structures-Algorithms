#include <iostream>
using namespace std;

// Swap two integers using pointers
void swapValues(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function used in QuickSort
int partition(int arr[], int start, int end) {
    int pivot = arr[end];      // Choose last element as pivot
    int index = start;

    for (int i = start; i < end; i++) {
        // If current element is smaller than pivot
        if (arr[i] < pivot) {
            swapValues(&arr[i], &arr[index]);
            index++;
        }
    }

    // Place pivot in its correct position
    swapValues(&arr[index], &arr[end]);

    return index;  // Return pivot index
}

// QuickSort algorithm
void quickSort(int arr[], int start, int end) {
    if (start < end) {
        int piv = partition(arr, start, end);

        // Recursively sort elements before and after partition
        quickSort(arr, start, piv - 1);
        quickSort(arr, piv + 1, end);
    }
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) cout << arr[i] << ' ';
    cout << '\n';
}

int main() {
    int arr[] = { 2, 7, 1, 3, 5, 6, 4 };
    int s = sizeof(arr) / sizeof(arr[0]);

    cout << "Original: ";
    printArray(arr, s);

    quickSort(arr, 0, s - 1);

    cout << "QuickSort: ";
    printArray(arr, s);

    return 0;
}
