#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#define ARRAY_SIZE_base 2

struct {
    const int small = 5;
    const int medium = 9;
    const int big = 13;
} ARRAY_SIZE_shift;

/*
array petit -> 32 elements (2 ^6)
array mitjà -> 1024 elements (2 ^10)
array gran -> 131072 elements (2 ^14)
*/

using namespace std;

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int size_shift) {
    for (int i = 0; i < (ARRAY_SIZE_base << size_shift) - 1; ++i) {
        for (int j = 0; j < (ARRAY_SIZE_base << size_shift) - i - 1; ++j) {
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j + 1]) {
                Swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int size_shift) {
    for (int i = 1; i < (ARRAY_SIZE_base << size_shift) - 1; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int size_shift) {
    for (int i = 0; i < (ARRAY_SIZE_base << size_shift) - 1; ++i) {
        // Find the minimum element in the unsorted part of the array
        int minIndex = i;
        for (int j = i + 1; j < (ARRAY_SIZE_base << size_shift); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element
        Swap(arr[i], arr[minIndex]);
    }
}

void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    int L[n1];
    int R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    // Merge the temporary arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Same as (left + right) / 2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

int main() {
    // De chatGPT

    // Specify the file name
    string filename = "arrays.txt";

    // Open the file for reading
    ifstream inputFile(filename);

    // Check if the file is open
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1; // Return an error code
    }
    cout << "file opened" << endl;

    inputFile >> noskipws;

    bool print_individual_time;
    char res;
    cout << "medir tiempo individualmente? (y/n): " << endl;
    cin >> res;
    print_individual_time = res == 'y';

    // Read data from the file
    char c;
    int i = 0;
    int line = 0;
    int shift;
    double total_time = 0;
    for (int j = 0; j < 4; ++j) {
        string s;
        while (inputFile >> c) {
            if (line < 20) 
                shift = ARRAY_SIZE_shift.small;
            else if (line < 40) 
                shift = ARRAY_SIZE_shift.medium;
            else
                shift = ARRAY_SIZE_shift.big;
            int arr[ARRAY_SIZE_base << shift];
            if (c == ' ') ++i;
            else if (c == '\n') {
                //increment line variable
                ++line;
                //time
                clock_t start_time = clock();
                //sort
                if (j == 0) {
                    bubbleSort(arr, shift);
                    s = "Bubble Sort";
                }
                else if (j == 1) {
                    insertionSort(arr, shift);
                    s = "Insertion Sort";
                }
                else if (j == 2) {
                    selectionSort(arr, shift);
                    s = "Selection Sort";
                }
                else {
                    mergeSort(arr, 0, (ARRAY_SIZE_base << shift) -1);
                    s = "Merge Sort";
                }
                clock_t end_time = clock();
                double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                total_time += duration;
                if (print_individual_time) cout << "Execution time of " << s << " for array size " << (ARRAY_SIZE_base << shift) << ": " << duration << " seconds" << endl;
                i = 0;
            }
            else arr[i] = int(c);
        }
        cout << "Execution time of " << s << " for 60 sorts of arrays of 3 sizes: " << total_time << "s" << endl;
        total_time = 0;
        line = 0;
        inputFile.clear();
        inputFile.seekg(0, std::ios::beg);
    }
    cout << endl;

    // Close the file when done
    inputFile.close();

    return 0; // Return success
}

