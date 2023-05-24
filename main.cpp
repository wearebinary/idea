#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        #pragma omp parallel for shared(arr, sorted)
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr(size);

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    // Sequential Bubble Sort
    vector<int> arrSeq = arr;
    double startTime = omp_get_wtime();
    sequentialBubbleSort(arrSeq);
    double endTime = omp_get_wtime();
    double sequentialTime = endTime - startTime;

    // Parallel Bubble Sort
    vector<int> arrPar = arr;
    startTime = omp_get_wtime();
    parallelBubbleSort(arrPar);
    endTime = omp_get_wtime();
    double parallelTime = endTime - startTime;

    // Print sorted arrays
    cout << "Sequential Bubble Sort:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arrSeq[i] << " ";
    }
    cout << endl;

    cout << "Parallel Bubble Sort:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arrPar[i] << " ";
    }
    cout << endl;

    // Performance comparison
    cout << "Sequential Bubble Sort Time: " << sequentialTime << " seconds" << endl;
    cout << "Parallel Bubble Sort Time: " << parallelTime << " seconds" << endl;

    return 0;
}
