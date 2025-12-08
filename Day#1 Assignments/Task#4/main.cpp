#include <iostream>
using namespace std;

// Iterative binary search on sorted array
int binarySearchIterative(const int arr[], int arraySize, int target) {
    int leftIndex = 0;
    int rightIndex = arraySize - 1;

    while (leftIndex <= rightIndex) {
        int midIndex = leftIndex + (rightIndex - leftIndex) / 2;

        if (arr[midIndex] == target) return midIndex;

        if (arr[midIndex] < target) leftIndex = midIndex + 1;

        else rightIndex = midIndex - 1;
    }
    return -1; // not found
}

// Recursive binary search helper
int binarySearchRecursive(const int arr[], int leftIndex, int rightIndex, int target) {
    if (leftIndex > rightIndex) return -1; // base: not found

    int midIndex = leftIndex + (rightIndex - leftIndex) / 2;

    if (arr[midIndex] == target) return midIndex;

    if (arr[midIndex] > target) return binarySearchRecursive(arr, leftIndex, midIndex - 1, target);

    return binarySearchRecursive(arr, midIndex + 1, rightIndex, target);
}

int main() {
    int sortedNumbers[] = { 2, 4, 6, 8, 10, 12, 14, 16 };
    int size = sizeof(sortedNumbers) / sizeof(sortedNumbers[0]);

    int target = 100;
    int i = binarySearchIterative(sortedNumbers, size, target);

    cout << "Iterative: ";
    if (i != -1){
            cout << "Found " << target << " at index " << i << '\n';
    }
    else cout << target << " Target not found\n";

    int r = binarySearchRecursive(sortedNumbers, 0, size - 1, target);
    cout << "Recursive: ";
    if (r != -1){
            cout << "Found " << target << " at index " << r << '\n';
    }
    else cout <<  target <<" Target not found\n";

    return 0;
}
