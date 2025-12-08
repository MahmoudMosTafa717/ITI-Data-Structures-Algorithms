#include <iostream>
using namespace std;

void bubbleSort(int arr[], int arraySize) {

    for (int i = 0; i < arraySize - 1; i++) {

        bool swapped = false;

        for (int j = 0; j < arraySize - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;

                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}


void printArray(const int arr[], int arraySize) {
    for (int i = 0; i < arraySize; ++i) cout << arr[i] << ' ';
    cout << '\n';
}

int main() {
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int s = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, s);

    bubbleSort(arr, s);

    cout << "Sorted array : ";
    printArray(arr, s);

    return 0;
}

