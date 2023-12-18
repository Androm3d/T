import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
//import java.time.Instant;
//import java.time.Duration;

public class sorts {
    static final int ARRAY_SIZE = 10000;

    static void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    static void bubbleSort(int[] arr) {
        for (int i = 0; i < arr.length - 1; ++i) {
            for (int j = 0; j < arr.length - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr, j, j + 1);
                }
            }
        }
    }

    static void insertionSort(int[] arr) {
        for (int i = 1; i < arr.length; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }

            arr[j + 1] = key;
        }
    }

    static void selectionSort(int[] arr) {
        for (int i = 0; i < arr.length - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < arr.length; ++j) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }

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
        System.arraycopy(arr, left, L, 0, n1);
        System.arraycopy(arr, middle + 1, R, 0, n2);

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
            int middle = left + (right - left) / 2;

            // Sort first and second halves
            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);

            // Merge the sorted halves
            merge(arr, left, middle, right);
        }
    }

     public static void main(String[] args) {
        // Specify the file name
        String filename = "arrays.txt";

        /*
        boolean printIndividualTime;
        System.out.println("Measure time individually? (y/n): ");
        char res = 0;
        try {
            res = (char) System.in.read();
        } catch (IOException e) {
            System.err.println("Error reading input");
            e.printStackTrace();
        }
        printIndividualTime = res == 'y';
        */

        // Read data from the file
        char c;
        int i = 0;
        int[] arr = new int[ARRAY_SIZE];
        double totalTime = 0;
        int line = 0;
        Boolean firstdigit = true; 
        String s = null;
        try (BufferedReader inputFile = new BufferedReader(new FileReader(filename))) {
            System.out.println("File opened");
            while ((c = (char) inputFile.read()) != -1 && line < 400) {
                Boolean newline = c == '\n';
                Boolean space = c == ' '; 
                if (newline) {
                    ++line;
                    //time
                    long startTime = System.nanoTime();
                    //Instant start = Instant.now();
                    //sort
                    if (line < 100) {
                        if (line == 0) System.out.println("\n\n");
                        bubbleSort(arr);
                        s = "Bubble Sort";
                    } else if (line < 200) {
                        if (line == 100) System.out.println("\n\n");
                        insertionSort(arr);
                        s = "Insertion Sort";
                    } else if (line < 300) {
                        if (line == 200) System.out.println("\n\n");
                        selectionSort(arr);
                        s = "Selection Sort";
                    } else {
                        if (line == 300) System.out.println("\n\n");
                        mergeSort(arr, 0, ARRAY_SIZE - 1);
                        s = "Merge Sort";
                    }
                    long endTime = System.nanoTime();
                    double duration = (endTime - startTime) / 1e9;
                    totalTime += duration;
                    /*
                    if (printIndividualTime) {
                        System.out.println("Execution time of " + s + ": " + duration + " seconds");
                        ++line;
                    }
                    */
                    //Instant end = Instant.now();
                    //Duration duration2 = Duration.between(start, end);
                    System.out.println(duration);
                    //System.out.println("instant: " + duration2);
                    i = 0;
                }
                else if (space) { // Check if the character is a digit
                    ++i;
                    firstdigit = true;
                }
                else{
                    if (firstdigit) {
                        arr[i] = c; 
                        firstdigit = false;
                    }
                    else {
                        arr[i] *= 10;
                        arr[i] += c;
                    }
                }
            }
            //System.out.println("Execution time of " + s + " for 100 sorts of arrays of size " + ARRAY_SIZE +
                    //": " + totalTime + "s");
            System.out.println();
            totalTime = 0;
        }
        catch (IOException e) {
        System.err.println("Error opening file: " + filename);
        e.printStackTrace();
        }
    }
}


