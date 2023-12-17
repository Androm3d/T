import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class sorts {

    static final int ARRAY_SIZE_BASE = 2;

    static class ArraySizeShift {
        final int small = 5;
        final int medium = 9;
        final int big = 13;
    }

    static ArraySizeShift ARRAY_SIZE_SHIFT = new ArraySizeShift();

    public static void main(String[] args) {
        // De chatGPT

        // Specify the file name
        String filename = "arrays.txt";

        try (BufferedReader inputFile = new BufferedReader(new FileReader(filename))) {
            System.out.println("file opened");

            boolean printIndividualTime;
            char res;
            System.out.print("medir tiempo individualmente? (y/n): ");
            res = (char) System.in.read();
            printIndividualTime = (res == 'y');

            // Read data from the file
            char c;
            int i = 0;
            int line = 0;
            int shift;
            double totalTime = 0;

            for (int j = 0; j < 4; ++j) {
                String s = null;

                while ((c = (char) inputFile.read()) != -1) {
                    if (line < 20)
                        shift = ARRAY_SIZE_SHIFT.small;
                    else if (line < 40)
                        shift = ARRAY_SIZE_SHIFT.medium;
                    else
                        shift = ARRAY_SIZE_SHIFT.big;

                    int[] arr = new int[ARRAY_SIZE_BASE << shift];

                    if (c == ' ')
                        ++i;
                    else if (c == '\n') {
                        // increment line variable
                        ++line;
                        // time
                        long startTime = System.nanoTime();
                        // sort
                        if (j == 0) {
                            bubbleSort(arr, shift);
                            s = "Bubble Sort";
                        } else if (j == 1) {
                            insertionSort(arr, shift);
                            s = "Insertion Sort";
                        } else if (j == 2) {
                            selectionSort(arr, shift);
                            s = "Selection Sort";
                        } else {
                            mergeSort(arr, 0, (ARRAY_SIZE_BASE << shift) - 1);
                            s = "Merge Sort";
                        }
                        long endTime = System.nanoTime();
                        double duration = (endTime - startTime) / 1e9;
                        totalTime += duration;
                        if (printIndividualTime) {
                            System.out.println("Execution time of " + s + " for array size " + (ARRAY_SIZE_BASE << shift)
                                    + ": " + duration + " seconds");
                        }
                        i = 0;
                    } else if (Character.isDigit(c))
                        arr[i] = Integer.parseInt(String.valueOf(c));
                }

                System.out.println(
                        "Execution time of " + s + " for 60 sorts of arrays of 3 sizes: " + totalTime + "s");
                totalTime = 0;
                line = 0;
                inputFile.reset();
            }

        } catch (IOException e) {
            System.err.println("Error opening file: " + filename);
            e.printStackTrace();
        }
    }

    static void bubbleSort(int[] arr, int sizeShift) {
        for (int i = 0; i < (ARRAY_SIZE_BASE << sizeShift) - 1; ++i) {
            for (int j = 0; j < (ARRAY_SIZE_BASE << sizeShift) - i - 1; ++j) {
                // Swap if the element found is greater than the next element
                if (arr[j] > arr[j + 1]) {
                    swap(arr, j, j + 1);
                }
            }
        }
    }

    static void insertionSort(int[] arr, int sizeShift) {
        for (int i = 1; i < (ARRAY_SIZE_BASE << sizeShift) - 1; ++i) {
            int key = arr[i];
            int j = i - 1;

            // Move elements of arr[0..i-1] that are greater than key to one position ahead of
            // their current position
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }

            arr[j + 1] = key;
        }
    }

    static void selectionSort(int[] arr, int sizeShift) {
        for (int i = 0; i < (ARRAY_SIZE_BASE << sizeShift) - 1; ++i) {
            // Find the minimum element in the unsorted part of the array
            int minIndex = i;
            for (int j = i + 1; j < (ARRAY_SIZE_BASE << sizeShift); ++j) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }

            // Swap the found minimum element with the first element
            swap(arr, i, minIndex);
        }
    }

    static void merge(int[] arr, int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        // Create temporary arrays
        int[] L = new int[n1];
        int[] R = new int[n2];

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

    static void mergeSort(int[] arr, int left, int right) {
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

    static void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}
