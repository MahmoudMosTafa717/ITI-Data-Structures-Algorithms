#include <iostream>
using namespace std;

int sequentialSearchSorted(const int arr[], int arraySize, int target) {
    for (int i = 0; i < arraySize; i++) {
        if (arr[i] == target) return i;       // found
        if (arr[i] > target) return -1;
    }
    return -1; // not found
}

int main() {
    int arr[] = { 1, 3, 5, 7, 9, 11, 13 };
    int s = sizeof(arr) / sizeof(arr[0]);

    int target = 7;
    int foundIndex = sequentialSearchSorted(arr, s, target);

    if (foundIndex != -1){
            cout << "Found " << target << " at index " << foundIndex << '\n';
    }
    else cout << target << " not found\n";

/********************************************************/

    int target2 = 6;
    cout << "Searching " << target2 << ": ";

    int index2 = sequentialSearchSorted(arr, s, target2);
    if (index2 != -1){
            cout << "Found at " << index2 << '\n';
    }
    else cout << "Not found\n";

    return 0;
}
