#include <iostream>
using namespace std;

void printArr(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

void selectionSort(int arr[], int iStart, int iEnd) {
    for (int i = iStart; i < iEnd; i++) {
        int minIndex = i;
        for (int j = i + 1; j <= iEnd; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}
void bubbleSort(int arr[], int iStart, int iEnd) {
    for (int i = iStart; i <= iEnd; i++) {
        for (int j = iStart; j < iEnd - (i - iStart); j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void insertionSort(int arr[], int iStart, int iEnd) {
    for (int i = iStart + 1; i <= iEnd; i++) {
        int val = arr[i];
        int j = i;
        while (j > iStart && arr[j - 1] > val) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = val;
    }
}

void merge(int arr[], int iStart, int mid, int iEnd) {
    int n1 = mid - iStart + 1;
    int n2 = iEnd - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[iStart + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = iStart;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L; delete[] R;
}
void mergeSort(int arr[], int iStart, int iEnd) {
    if (iStart < iEnd) {
        int mid = iStart + (iEnd - iStart) / 2;
        mergeSort(arr, iStart, mid);
        mergeSort(arr, mid + 1, iEnd);
        merge(arr, iStart, mid, iEnd);
    }
}

int partition(int arr[], int iStart, int iEnd) {
    int pivot = arr[iEnd];
    int i = (iStart - 1);
    for (int j = iStart; j < iEnd; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[iEnd]);
    return (i + 1);
}
void quickSort(int arr[], int iStart, int iEnd) {
    if (iStart < iEnd) {
        int pi = partition(arr, iStart, iEnd);
        quickSort(arr, iStart, pi - 1);
        quickSort(arr, pi + 1, iEnd);
    }
}

int main() {
    int size = 10;
    int original[size] = { 46, 14, 33, 27, 10, 35, 19, 42, 31, 26 }; 
    int arr[size];

    cout << "Original array: ";
    printArr(original, size);

    copyArray(original, arr, size);
    selectionSort(arr, 0, size - 1);
    cout << "Selection Sort: "; 
    printArr(arr, size);

    copyArray(original, arr, size);
    bubbleSort(arr, 0, size - 1);
    cout << "Bubble Sort:    "; 
    printArr(arr, size);

    copyArray(original, arr, size);
    insertionSort(arr, 0, size - 1);
    cout << "Insertion Sort: "; 
    printArr(arr, size);

    copyArray(original, arr, size);
    mergeSort(arr, 0, size - 1);
    cout << "Merge Sort:     "; 
    printArr(arr, size);

    copyArray(original, arr, size);
    quickSort(arr, 0, size - 1);
    cout << "Quick Sort:     "; 
    printArr(arr, size);

    cout << "\n";
    system("pause>0");
    return 0;
}