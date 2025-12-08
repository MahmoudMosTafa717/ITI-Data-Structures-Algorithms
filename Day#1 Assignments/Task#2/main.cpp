#include <iostream>
using namespace std;

// Merge two sorted subarrays arr[left,mid] and arr[mid+1,right]
void merge(int arr[], int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int* leftArr = new int[leftSize];
    int* rightArr = new int[rightSize];

    for (int i = 0; i < leftSize; ++i){
            leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < rightSize; ++j){
            rightArr[j] = arr[mid + 1 + j];
    }

    // Merge back into arr[left,right]
    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }
    // Copy any remaining elements
    while (i < leftSize) arr[k++] = leftArr[i++];
    while (j < rightSize) arr[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;
}

//  Merge Sort => Recursively Divide
void mergeSort(int arr[], int left, int right) {
     // base case: one element
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Sort left half
    mergeSort(arr, left, mid);

    // Sort right half
    mergeSort(arr, mid + 1, right);

    // Merge sorted halves
    merge(arr, left, mid, right);
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) cout << arr[i] << ' ';
    cout << '\n';
}

int main() {
    int values[] = { 38, 27, 43, 3, 9, 82, 10 };
    int size = sizeof(values) / sizeof(values[0]);

    cout << "Original: ";
    printArray(values, size);

    mergeSort(values, 0, size - 1);

    cout << "Merge Sort: ";
    printArray(values, size);
    return 0;
}
