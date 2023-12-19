#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
//#include <chrono>

#define ARRAY_SIZE 10000

/*
array petit -> 32 elements (2 ^6)
array mitjà -> 1024 elements (2 ^10)
array gran ->  elements (2 ^14)
*/

using namespace std;

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int size_shift) {
    for (int i = 0; i < ARRAY_SIZE - 1; ++i) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; ++j) {
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j + 1]) {
                Swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int size_shift) {
    for (int i = 1; i < ARRAY_SIZE - 1; ++i) {
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
    for (int i = 0; i < ARRAY_SIZE - 1; ++i) {
        // Find the minimum element in the unsorted part of the array
        int minIndex = i;
        for (int j = i + 1; j < ARRAY_SIZE; ++j) {
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

/*
void printarray(int arr[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) cout << arr[i] << ' ';
    cout << endl;
}
*/

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
    //cout << "file opened" << endl;

    inputFile >> noskipws;

    /*
    bool print_individual_time;
    char res;
    cout << "medir tiempo individualmente? (y/n): " << endl;
    cin >> res;
    print_individual_time = res == 'y';
    */

    // Read data from the file
    char c;
    int i = 0;
    int shift;
    int arr[ARRAY_SIZE];
    double total_time = 0;
    int line = 0;
    bool firstdigit = true;
    string s;
    while (inputFile >> c) {
        bool newline = c == '\n';
        bool space = c == ' '; 
        if (newline) {
            ++line;
            //time
            clock_t start_time = clock();
            //auto start_time2 = chrono::high_resolution_clock::now();
            //sort
            if (line < 100) {
                if (line == 1) cout << endl << endl << endl;
                bubbleSort(arr, shift);
                s = "Bubble Sort";
            }
            else if (line < 200) {
                if (line == 100) cout << endl << endl << endl;
                insertionSort(arr, shift);
                s = "Insertion Sort";
            }
            else if (line < 300) {
                if (line == 200) cout << endl << endl << endl;
                selectionSort(arr, shift);
                s = "Selection Sort";
            }
            else {
                if (line == 300) cout << endl << endl << endl;
                mergeSort(arr, 0, ARRAY_SIZE -1);
                s = "Merge Sort";
            }
            clock_t end_time = clock();
            double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            total_time += duration;
            //if (print_individual_time) cout << "Execution time of " << s << " for array size " << ARRAY_SIZE << ": " << duration << " seconds" << endl;
            /*
            auto end_time2 = chrono::high_resolution_clock::now();
            double duration2 =  chrono::duration_cast<chrono::microseconds>(end_time2 - start_time2).count() / 1e6;*/
            
            cout << duration << endl;
            
            //cout << "ctime: " << duration << endl;
            //cout << "chrono: " << duration2 << endl;
            //cout << s << endl << endl << endl << endl;
            //printarray(arr);

            i = 0;
        }
        else if (space) {
            ++i;
            firstdigit = true;
        }
        else {
            if (firstdigit) {
                arr[i] = int(c) - 48; //int retorna el valor en ASCII, 48 és '0' en ASCII
                firstdigit = false;
            }
            else {
                arr[i] *= 10;
                arr[i] += int(c) - 48;
            }
        }   
    }
    //cout << "Execution time of " << s << " for 60 sorts of arrays of sizes " << ARRAY_SIZE << ": " << total_time << "s" << endl;
    cout << endl << endl << endl;
    total_time = 0;
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);
    cout << endl;

    // Close the file when done
    inputFile.close();

    return 0; // Return success
}

