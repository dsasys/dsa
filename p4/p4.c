#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/resource.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted with node i which is an index in arr[]
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main function to perform heap sort
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    gettimeofday(&tv1, NULL);

    heapSort(arr, n);

    gettimeofday(&tv2, NULL);

    printf("Sorted array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Time of heap sort is: %f microseconds\n", (double)(tv2.tv_usec - tv1.tv_usec));

    getrusage(RUSAGE_SELF, &r_usage);

    printf("Memory used: %ld bytes\n", r_usage.ru_maxrss * 1024);

    return 0;
}
